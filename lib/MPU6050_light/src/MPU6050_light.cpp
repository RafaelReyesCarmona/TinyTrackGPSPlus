/* MPU6050_light library for Arduino
 * 
 * Authors: Romain JL. Fétick (github.com/rfetick)
 *              simplifications and corrections
 *          Tockn (github.com/tockn)
 *              initial author (v1.5.2)
 */

#include "MPU6050_light.h"
#include "Arduino.h"

/* INIT and BASIC FUNCTIONS */

MPU6050::MPU6050(TwoWire &w){
  wire = &w;
  setFilterGyroCoef(DEFAULT_GYRO_COEFF);
  setGyroOffsets(0,0,0);
  setAccOffsets(0,0,0);
}

byte MPU6050::begin(int gyro_config_num, int acc_config_num){
  writeData(MPU6050_SMPLRT_DIV_REGISTER, 0x00);
  writeData(MPU6050_CONFIG_REGISTER, 0x00);
  setGyroConfig(gyro_config_num);
  setAccConfig(acc_config_num);
  byte status = writeData(MPU6050_PWR_MGMT_1_REGISTER, 0x01); // check only the last connection with status
  
  this->update();
  angleX = this->getAccAngleX();
  angleY = this->getAccAngleY();
  preInterval = millis(); // may cause issue if begin() is much before the first update()
  return status;
}

byte MPU6050::writeData(byte reg, byte data){
  wire->beginTransmission(MPU6050_ADDR);
  wire->write(reg);
  wire->write(data);
  byte status = wire->endTransmission();
  return status; // 0 if success
}

// This method is not used internaly, maybe by user...
byte MPU6050::readData(byte reg) {
  wire->beginTransmission(MPU6050_ADDR);
  wire->write(reg);
  wire->endTransmission(true);
  wire->requestFrom(MPU6050_ADDR, 1);
  byte data =  wire->read();
  return data;
}

/* SETTER */

byte MPU6050::setGyroConfig(int config_num){
  byte status;
  switch(config_num){
    case 0: // range = +- 250 °/s
	  gyro_lsb_to_degsec = 131.0;
	  status = writeData(MPU6050_GYRO_CONFIG_REGISTER, 0x00);
	  break;
	case 1: // range = +- 500 °/s
	  gyro_lsb_to_degsec = 65.5;
	  status = writeData(MPU6050_GYRO_CONFIG_REGISTER, 0x08);
	  break;
	case 2: // range = +- 1000 °/s
	  gyro_lsb_to_degsec = 32.8;
	  status = writeData(MPU6050_GYRO_CONFIG_REGISTER, 0x10);
	  break;
	case 3: // range = +- 2000 °/s
	  gyro_lsb_to_degsec = 16.4;
	  status = writeData(MPU6050_GYRO_CONFIG_REGISTER, 0x18);
	  break;
	default: // error
	  status = 1;
	  break;
  }
  return status;
}

byte MPU6050::setAccConfig(int config_num){
  byte status;
  switch(config_num){
    case 0: // range = +- 2 g
	  acc_lsb_to_g = 16384.0;
	  status = writeData(MPU6050_ACCEL_CONFIG_REGISTER, 0x00);
	  break;
	case 1: // range = +- 4 g
	  acc_lsb_to_g = 8192.0;
	  status = writeData(MPU6050_ACCEL_CONFIG_REGISTER, 0x08);
	  break;
	case 2: // range = +- 8 g
	  acc_lsb_to_g = 4096.0;
	  status = writeData(MPU6050_ACCEL_CONFIG_REGISTER, 0x10);
	  break;
	case 3: // range = +- 16 g
	  acc_lsb_to_g = 2048.0;
	  status = writeData(MPU6050_ACCEL_CONFIG_REGISTER, 0x18);
	  break;
	default: // error
	  status = 1;
	  break;
  }
  return status;
}

void MPU6050::setGyroOffsets(float x, float y, float z){
  gyroXoffset = x;
  gyroYoffset = y;
  gyroZoffset = z;
  gyroXoffsetRaw = (int16_t)(x*gyro_lsb_to_degsec);
  gyroYoffsetRaw = (int16_t)(y*gyro_lsb_to_degsec);
  gyroZoffsetRaw = (int16_t)(z*gyro_lsb_to_degsec);
}

void MPU6050::setAccOffsets(float x, float y, float z){
  accXoffset = x;
  accYoffset = y;
  accZoffset = z;
  accXoffsetRaw = (int16_t)(x*acc_lsb_to_g);
  accYoffsetRaw = (int16_t)(y*acc_lsb_to_g);
  accZoffsetRaw = (int16_t)(z*acc_lsb_to_g);
}

void MPU6050::setGyroOffsetsRaw(int16_t x, int16_t y, int16_t z){
  gyroXoffset = (float)x / gyro_lsb_to_degsec;
  gyroYoffset = (float)y / gyro_lsb_to_degsec;
  gyroZoffset = (float)z / gyro_lsb_to_degsec;
  gyroXoffsetRaw = x;
  gyroYoffsetRaw = y;
  gyroZoffsetRaw = z;
}

void MPU6050::setAccOffsetsRaw(int16_t x, int16_t y, int16_t z){
  accXoffset = (float)x / acc_lsb_to_g;
  accYoffset = (float)y / acc_lsb_to_g;
  accZoffset = (float)z / acc_lsb_to_g;
  accXoffsetRaw = x;
  accYoffsetRaw = y;
  accZoffsetRaw = z;
}

void MPU6050::setFilterGyroCoef(float gyro_coeff){
  if ((gyro_coeff<0) or (gyro_coeff>1)){ gyro_coeff = DEFAULT_GYRO_COEFF; } // prevent bad gyro coeff, should throw an error...
  filterGyroCoef = gyro_coeff;
}

void MPU6050::setFilterAccCoef(float acc_coeff){
  setFilterGyroCoef(1.0-acc_coeff);
}

/* CALC OFFSET */

void MPU6050::calcOffsets(bool is_calc_gyro, bool is_calc_acc){
  if(is_calc_gyro){ setGyroOffsets(0,0,0); }
  if(is_calc_acc){ setAccOffsets(0,0,0); }
  float ag[6] = {0,0,0,0,0,0}; // 3*acc, 3*gyro
  
  for(int i = 0; i < CALIB_OFFSET_NB_MES; i++){
    this->fetchData();
	ag[0] += accX;
	ag[1] += accY;
	ag[2] += (accZ-1.0);
	ag[3] += gyroX;
	ag[4] += gyroY;
	ag[5] += gyroZ;
	delay(1); // wait a little bit between 2 measurements
  }
  
  if(is_calc_acc){
    accXoffset = ag[0] / CALIB_OFFSET_NB_MES;
    accYoffset = ag[1] / CALIB_OFFSET_NB_MES;
    accZoffset = ag[2] / CALIB_OFFSET_NB_MES;
    accXoffsetRaw = accXoffset * acc_lsb_to_g;
    accYoffsetRaw = accYoffset * acc_lsb_to_g;
    accZoffsetRaw = accZoffset * acc_lsb_to_g;
    
    Serial.println("AccOffset calibration data:");
    Serial.print("accXoffset:\t");Serial.print(accXoffset,8);Serial.print("\t");Serial.println(accXoffsetRaw);
    Serial.print("accYoffset:\t");Serial.print(accYoffset,8);Serial.print("\t");Serial.println(accYoffsetRaw);
    Serial.print("accZoffset:\t");Serial.print(accZoffset,8);Serial.print("\t");Serial.println(accZoffsetRaw);
  }
  
  if(is_calc_gyro){
    gyroXoffset = ag[3] / CALIB_OFFSET_NB_MES;
    gyroYoffset = ag[4] / CALIB_OFFSET_NB_MES;
    gyroZoffset = ag[5] / CALIB_OFFSET_NB_MES;
    gyroXoffsetRaw = gyroXoffset * gyro_lsb_to_degsec;
    gyroYoffsetRaw = gyroYoffset * gyro_lsb_to_degsec;
    gyroZoffsetRaw = gyroZoffset * gyro_lsb_to_degsec;

    Serial.println("GyroOffset calibration data:");
    Serial.print("gyroXoffset:\t");Serial.print(gyroXoffset,8);Serial.print("\t");Serial.println(gyroXoffsetRaw);
    Serial.print("gyroYoffset:\t");Serial.print(gyroYoffset,8);Serial.print("\t");Serial.println(gyroYoffsetRaw);
    Serial.print("gyroZoffset:\t");Serial.print(gyroZoffset,8);Serial.print("\t");Serial.println(gyroZoffsetRaw);
  }
}

/* UPDATE */

void MPU6050::fetchData(){
  wire->beginTransmission(MPU6050_ADDR);
  wire->write(MPU6050_ACCEL_OUT_REGISTER);
  wire->endTransmission(false);
  wire->requestFrom((int)MPU6050_ADDR, 14);

  int16_t rawData[7]; // [ax,ay,az,temp,gx,gy,gz]

  for(int i=0;i<7;i++){
	rawData[i]  = wire->read() << 8;
    rawData[i] |= wire->read();
  }

  accX = ((float)rawData[0]) / acc_lsb_to_g - accXoffset;
  accY = ((float)rawData[1]) / acc_lsb_to_g - accYoffset;
  accZ = ((float)rawData[2]) / acc_lsb_to_g - accZoffset;
  temp = (rawData[3] + TEMP_LSB_OFFSET) / TEMP_LSB_2_DEGREE;
  gyroX = ((float)rawData[4]) / gyro_lsb_to_degsec - gyroXoffset;
  gyroY = ((float)rawData[5]) / gyro_lsb_to_degsec - gyroYoffset;
  gyroZ = ((float)rawData[6]) / gyro_lsb_to_degsec - gyroZoffset;
}

void MPU6050::fetchDataRaw(){
  wire->beginTransmission(MPU6050_ADDR);
  wire->write(MPU6050_ACCEL_OUT_REGISTER);
  wire->endTransmission(false);
  wire->requestFrom((int)MPU6050_ADDR, 14);

  int16_t rawData[7]; // [ax,ay,az,temp,gx,gy,gz]

  for(int i=0;i<7;i++){
	rawData[i]  = wire->read() << 8;
    rawData[i] |= wire->read();
  }

  accX_raw = rawData[0] - accXoffsetRaw;
  accY_raw = rawData[1] - accYoffsetRaw;
  accZ_raw = rawData[2] - accZoffsetRaw;
  temp_raw = rawData[3] + TEMP_LSB_OFFSET;
  gyroX_raw = rawData[4] - gyroXoffsetRaw;
  gyroY_raw = rawData[5] - gyroYoffsetRaw;
  gyroZ_raw = rawData[6] - gyroZoffsetRaw;
}

void MPU6050::update(){
  // retrieve raw data
  this->fetchData();
  //this->fetchDataRaw();
  
  // process data to get angles
  float sgZ = (accZ>=0)-(accZ<0);
  angleAccX = atan2(accY, sgZ*sqrt(accZ*accZ + accX*accX)) * RAD_2_DEG;
  angleAccY = - atan2(accX, sqrt(accZ*accZ + accY*accY)) * RAD_2_DEG;

  unsigned long Tnew = millis();
  float dt = (Tnew - preInterval) * 1e-3;
  preInterval = Tnew;

  angleX = (filterGyroCoef*(angleX + gyroX*dt)) + ((1.0-filterGyroCoef)*angleAccX);
  angleY = (filterGyroCoef*(angleY + gyroY*dt)) + ((1.0-filterGyroCoef)*angleAccY);
  angleZ += gyroZ*dt;

}
