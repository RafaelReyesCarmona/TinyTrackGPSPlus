/* The register map is provided at
 * https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf
 *
 * Mapping of the different gyro and accelero configurations:
 *
 * GYRO_CONFIG_[0,1,2,3] range = +- [250, 500,1000,2000] °/s
 *                       sensi =    [131,65.5,32.8,16.4] bit/(°/s)
 *
 * ACC_CONFIG_[0,1,2,3] range = +- [    2,   4,   8,  16] times the gravity (9.81m/s²)
 *                      sensi =    [16384,8192,4096,2048] bit/gravity
*/

#ifndef MPU6050_LIGHT_H
#define MPU6050_LIGHT_H

#include "Arduino.h"
#include "Wire.h"

#define MPU6050_ADDR                  0x69
#define MPU6050_SMPLRT_DIV_REGISTER   0x19
#define MPU6050_CONFIG_REGISTER       0x1a
#define MPU6050_GYRO_CONFIG_REGISTER  0x1b
#define MPU6050_ACCEL_CONFIG_REGISTER 0x1c
#define MPU6050_PWR_MGMT_1_REGISTER   0x6b

#define MPU6050_GYRO_OUT_REGISTER     0x43
#define MPU6050_ACCEL_OUT_REGISTER    0x3B

//#define RAD_2_DEG             57.29578 // [°/rad]
#define RAD_2_DEG             180.0/PI
#define CALIB_OFFSET_NB_MES   500
#define TEMP_LSB_2_DEGREE     340.0    // [bit/celsius]
#define TEMP_LSB_OFFSET       12412.0

#define DEFAULT_GYRO_COEFF    0.98

class MPU6050{
  public:
    // INIT and BASIC FUNCTIONS
	MPU6050(TwoWire &w);
    byte begin(int gyro_config_num=1, int acc_config_num=0);
	
	byte writeData(byte reg, byte data);
    byte readData(byte reg);
	
	void calcOffsets(bool is_calc_gyro=true, bool is_calc_acc=true);
	void calcGyroOffsets(){ calcOffsets(true,false); }; // retro-compatibility with v1.0.0
	void calcAccOffsets(){ calcOffsets(false,true); }; // retro-compatibility with v1.0.0
	
	// MPU CONFIG SETTER
	byte setGyroConfig(int config_num);
	byte setAccConfig(int config_num);
	float getGyroConfig(){ return gyro_lsb_to_degsec; };
	float getAccConfig(){ return acc_lsb_to_g; };
	
    void setGyroOffsets(float x, float y, float z);
	void setAccOffsets(float x, float y, float z);
    void setGyroOffsetsRaw(int16_t x, int16_t y, int16_t z);
	void setAccOffsetsRaw(int16_t x, int16_t y, int16_t z);
	
	void setFilterGyroCoef(float gyro_coeff);
	void setFilterAccCoef(float acc_coeff);

	// MPU CONFIG GETTER
	float getGyroXoffset(){ return gyroXoffset; };
    float getGyroYoffset(){ return gyroYoffset; };
    float getGyroZoffset(){ return gyroZoffset; };
	
	float getAccXoffset(){ return accXoffset; };
	float getAccYoffset(){ return accYoffset; };
	float getAccZoffset(){ return accZoffset; };
	
	float getFilterGyroCoef(){ return filterGyroCoef; };
	float getFilterAccCoef(){ return 1.0-filterGyroCoef; };
	
	// INLOOP GETTER
    float getTemp(){ return temp; };

    float getAccX(){ return accX; };
    float getAccY(){ return accY; };
    float getAccZ(){ return accZ; };

    float getGyroX(){ return gyroX; };
    float getGyroY(){ return gyroY; };
    float getGyroZ(){ return gyroZ; };

    int16_t getTempRaw(){ return temp_raw; };

    int16_t getAccXRaw(){ return accX_raw; };
    int16_t getAccYRaw(){ return accY_raw; };
    int16_t getAccZRaw(){ return accZ_raw; };

    int16_t getGyroXRaw(){ return gyroX_raw; };
    int16_t getGyroYRaw(){ return gyroY_raw; };
    int16_t getGyroZRaw(){ return gyroZ_raw; };
	
	float getAccAngleX(){ return angleAccX; };
    float getAccAngleY(){ return angleAccY; };
    
	float getAngleInclX(){ return angleInclX; };
    float getAngleInclY(){ return angleInclY; };

    float getAngleX(){ return angleX; };
    float getAngleY(){ return angleY; };
    float getAngleZ(){ return angleZ; };

	// INLOOP UPDATE
	void fetchDataRaw(); // get new data values in raw.
	void fetchData(); // user should better call 'update' that includes 'fetchData'
    void update();


  private:
    TwoWire *wire;
    int16_t temp_raw, accX_raw, accY_raw, accZ_raw, gyroX_raw, gyroY_raw, gyroZ_raw;
	float gyro_lsb_to_degsec, acc_lsb_to_g;
    float gyroXoffset, gyroYoffset, gyroZoffset;
    int16_t gyroXoffsetRaw, gyroYoffsetRaw, gyroZoffsetRaw;
	float accXoffset, accYoffset, accZoffset;
	int16_t accXoffsetRaw, accYoffsetRaw, accZoffsetRaw;
    float temp, accX, accY, accZ, gyroX, gyroY, gyroZ;
    float angleAccX, angleAccY;
    float angleInclX, angleInclY;
    float angleX, angleY, angleZ;
    long preInterval;
    float filterGyroCoef; // complementary filter coefficient to balance gyro vs accelero data to get angle
};

#endif
