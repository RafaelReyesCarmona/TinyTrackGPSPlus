/**
 * @file FusionGPS.h
 * @author Rafael Reyes
 * @brief Algorithm to combine GPS data with AHRS.
 */

//------------------------------------------------------------------------------
// Includes

#include <float.h> // FLT_MAX
#include "FusionGPS.h"
#include <math.h> // atan2f, cosf, powf, sinf

//------------------------------------------------------------------------------
// Definitions

//------------------------------------------------------------------------------
// Constants

// acceleration due to gravity
const float G = 9.807f;
// major eccentricity squared
const double ECC2 = 673949675659e-14;//0.0066943799901;
// earth semi-major axis radius (m)
const double EARTH_RADIUS = 6378137.0;
// GPS measurement noise std dev (m)
const float SIG_GPS_P_NE = 3.5f;
const float SIG_GPS_P_D = 5.0f;
// GPS measurement noise std dev (m/s)
const float SIG_GPS_V = 1.2f;

#define     Rew     		6.359058719353925e+006      //earth radius
#define     Rns     		6.386034030458164e+006      //earth radius

//------------------------------------------------------------------------------
// Function declarations

//------------------------------------------------------------------------------
// Functions

/**
 * @brief 
 * @param GPS GPS algorithm structure.
 */
void FusionGPSInitialise(FusionGPS *const GPS) {
    const FusionGPSSettings settings = {
            .convention = FusionConventionNed,
            .gain = 0.5f,
            .locationRejection = 90.0f,
            .velocityRejection = 90.0f,
            .rejectionTimeout = 0,
    };
    FusionGPSSetSettings(GPS, &settings);
    FusionGPSReset(GPS);
}

/**
 * @brief 
 * @param GPS GPS algorithm structure.
 */
void FusionGPSReset(FusionGPS *const GPS) {
    GPS->location_ins = FUSION_VECTORDOUBLE_ZERO;
    GPS->location = FUSION_VECTORDOUBLE_ZERO;
    GPS->velocity_ins = FUSION_VECTOR_ZERO;
    GPS->velocity = FUSION_VECTOR_ZERO;
    GPS->K = FUSION_VECTOR_ZERO;
    GPS->P = FUSION_VECTOR_ONES;
    GPS->K_vel = FUSION_VECTOR_ZERO;
    GPS->P_vel = FUSION_VECTOR_ONES;
    GPS->initialising = false;
    GPS->locationIgnored = false;
    GPS->locationRejectionTimer = 0;
    GPS->locationRejectionTimeout = false;
    GPS->velocityIgnored = false;
    GPS->velocityRejectionTimer = 0;
    GPS->velocityRejectionTimeout = false;
}

/**
 * @brief 
 * @param GPS GPS algorithm structure.
 * @param settings 
 */
void FusionGPSSetSettings(FusionGPS *const GPS, const FusionGPSSettings *const settings) {
    GPS->settings.convention = settings->convention;
    GPS->settings.gain = settings->gain;
    if ((settings->locationRejection == 0.0f) || (settings->rejectionTimeout == 0)) {
        GPS->settings.locationRejection = FLT_MAX;
    } else {
        GPS->settings.locationRejection = powf(0.5f * sinf(FusionDegreesToRadians(settings->locationRejection)), 2);
    }
    if ((settings->velocityRejection == 0.0f) || (settings->rejectionTimeout == 0)) {
        GPS->settings.velocityRejection = FLT_MAX;
    } else {
        GPS->settings.velocityRejection = powf(0.5f * sinf(FusionDegreesToRadians(settings->velocityRejection)), 2);
    }
    GPS->settings.rejectionTimeout = settings->rejectionTimeout;
    if (GPS->initialising == false) {
      
    }
}

/**
 * @brief 
 * @param GPS GPS algorithm structure.
 */
void FusionGPSAHRSUpdate(FusionGPS *const GPS, const FusionQuaternion quaternium, const FusionVector accel, const float deltaTime) {
  if(GPS->initialising) {
    FusionVector GPS_pos_rad, GPS_pos_ins_rad;

    GPS->angular = FusionQuaternionAngularVelocity(GPS->quaternium, quaternium, deltaTime);
    //if(sqrt(FusionVectorMagnitudeSquared(GPS->angular))>0.1f) {
    const FusionMatrix quad = FusionQuaternionToMatrix(quaternium);
    float R = (GPS->quaternium.element.w + quaternium.element.w) / 2.0f;
    GPS->quaternium = quaternium;
    FusionVector velocity = FusionVectorMultiplyScalar(GPS->angular,R);

    GPS_pos_rad.axis.x = FusionDegreesToRadians(GPS->location_ahrs.axis.x);
    GPS_pos_rad.axis.y = FusionDegreesToRadians(GPS->location_ahrs.axis.y);
    GPS_pos_rad.axis.z = GPS->location_ahrs.axis.z;
  
    GPS->dx = FusionMatrixMultiplyVectorDouble(quad, accel);
    GPS->dxd = FusionGPSposrate(GPS->velocity_ins, GPS_pos_rad);
    GPS->velocity_ins = FusionVectorAdd(velocity ,FusionVectorMultiplyScalarDouble(GPS->dx,deltaTime));
    
    GPS_pos_ins_rad = FusionVectorAdd(GPS_pos_rad ,FusionVectorMultiplyScalarDouble(GPS->dxd,deltaTime));

    GPS->location_ins.axis.x = FusionRadiansToDegrees(GPS_pos_ins_rad.axis.x);
    GPS->location_ins.axis.y = FusionRadiansToDegrees(GPS_pos_ins_rad.axis.y);
    GPS->location_ins.axis.z = GPS_pos_ins_rad.axis.z;
    GPS->location_ahrs = GPS->location_ins;
    //}
  }
}

/**
 * @brief 
 * @param GPS GPS algorithm structure.
 */
void FusionGPSUpdate(FusionGPS *const GPS, const FusionVectorDouble pos, const FusionVector vel, const FusionVector GPS_error) {
  FusionVector pos_ned_ins, pos_ned_gps, pos_prev_ned_gps;
  FusionVectorDouble pos_ecef_ins, pos_ecef_gps, pos_prev_ecef_gps;
  FusionVector GPS_pos_rad, GPS_pos_ins_rad, GPS_pos_prev_rad, GPS_pos_prev_ins_rad;
  FusionVector velocity_y, location_y, location_prev_y;

  // ... R
  const FusionVector R = { .axis = {
    .x = SIG_GPS_P_NE,
    .y = SIG_GPS_P_NE,
    .z = SIG_GPS_P_D*SIG_GPS_P_D
  }};
  /*
  const FusionVector R_vel = { .axis = {
    .x = SIG_GPS_V*SIG_GPS_V,
    .y = SIG_GPS_V*SIG_GPS_V,
    .z = SIG_GPS_V*SIG_GPS_V
  }};
  */
  if(!GPS->initialising) {
    GPS->location = pos;
    GPS->velocity = vel;
    
    GPS_pos_rad.axis.x = FusionDegreesToRadians(pos.axis.x);
    GPS_pos_rad.axis.y = FusionDegreesToRadians(pos.axis.y);
    GPS_pos_rad.axis.z = pos.axis.z;

    float Kalman_init = (1.0-(1/SIG_GPS_P_NE+1.0));

    GPS_pos_ins_rad.axis.z = GPS_pos_rad.axis.z; 
    GPS_pos_ins_rad.axis.x = GPS_pos_rad.axis.x + (GPS_error.axis.x*Kalman_init) / (Rew + GPS_pos_ins_rad.axis.z);
    GPS_pos_ins_rad.axis.y = GPS_pos_rad.axis.y + ((GPS_error.axis.y*Kalman_init) / (Rns + GPS_pos_ins_rad.axis.z)) / cos(GPS_pos_ins_rad.axis.x);

    GPS->location_ins.axis.x = FusionRadiansToDegrees(GPS_pos_ins_rad.axis.x);
    GPS->location_ins.axis.y = FusionRadiansToDegrees(GPS_pos_ins_rad.axis.y);
    GPS->location_ins.axis.z = GPS_pos_ins_rad.axis.z;
    GPS->velocity_ins = vel;
    GPS->location_ahrs = pos;
    GPS->initialising = true;
  } else {
    GPS->velocity = vel;

    GPS_pos_rad.axis.x = FusionDegreesToRadians(pos.axis.x);
    GPS_pos_rad.axis.y = FusionDegreesToRadians(pos.axis.y);
    GPS_pos_rad.axis.z = pos.axis.z;
    GPS_pos_prev_rad.axis.x = FusionDegreesToRadians(GPS->location.axis.x);
    GPS_pos_prev_rad.axis.y = FusionDegreesToRadians(GPS->location.axis.y);
    GPS_pos_prev_rad.axis.z = GPS->location.axis.z;
    GPS_pos_prev_ins_rad.axis.x = FusionDegreesToRadians(GPS->location_ins.axis.x);
    GPS_pos_prev_ins_rad.axis.y = FusionDegreesToRadians(GPS->location_ins.axis.y);
    GPS_pos_prev_ins_rad.axis.z = GPS->location_ins.axis.z;

    pos_ecef_gps = FusionGPSpos2ecef(GPS_pos_rad);
    pos_ned_gps = FusionGPSecef2ned(pos_ecef_gps, GPS_pos_rad);
    pos_prev_ecef_gps = FusionGPSpos2ecef(GPS_pos_prev_rad);
    pos_prev_ned_gps = FusionGPSecef2ned(pos_prev_ecef_gps, GPS_pos_prev_rad);
    pos_ecef_ins = FusionGPSpos2ecef(GPS_pos_prev_ins_rad);
    pos_ned_ins = FusionGPSecef2ned(pos_ecef_ins, GPS_pos_prev_ins_rad);
    location_y = FusionVectorSubtract(pos_ned_gps, pos_ned_ins);
    location_prev_y = FusionVectorSubtract(pos_ned_gps, pos_prev_ned_gps);
    //velocity_y = FusionVectorSubtract(vel, GPS->velocity_ins);

    FusionVector K_inv = FusionVectorAdd(GPS->P, R);
    GPS->K = (FusionVector){.axis = {
      .x = 1 / K_inv.axis.x,
      .y = 1 / K_inv.axis.y,
      .z = 1 / K_inv.axis.z,
    }};
    /*
    FusionVector K_vel_inv = FusionVectorAdd(GPS->P_vel, R_vel);
    GPS->K_vel = (FusionVector){.axis = {
      .x = 1 / K_vel_inv.axis.x,
      .y = 1 / K_vel_inv.axis.y,
      .z = 1 / K_vel_inv.axis.z,
    }};
    */
    FusionVector P_AB = FusionVectorSubtract(FUSION_VECTOR_ONES, GPS->K);
    FusionVector P_C = FusionVectorHadamardProduct(P_AB,GPS->K);
    GPS->P = (FusionVector){.axis = {
      .x = P_AB.axis.x * P_AB.axis.x + P_C.axis.x,
      .y = P_AB.axis.y * P_AB.axis.y + P_C.axis.y,
      .z = P_AB.axis.z * P_AB.axis.z + P_C.axis.z,
    }};
    const float alfa = 0.90f;
    location_y = FusionVectorMultiplyScalar(location_y,alfa);
    location_prev_y = FusionVectorMultiplyScalar(location_prev_y,(1.0f-alfa));
    
    FusionVector location_y_filtered;
    location_y_filtered = FusionVectorAdd(location_y,location_prev_y);
    FusionVector GPS_kalman_rad = FusionVectorHadamardProduct(GPS->K, location_y_filtered); //x = K *y
/*
    FusionVector P_vel_AB = FusionVectorSubtract(FUSION_VECTOR_ONES, GPS->K_vel);
    FusionVector P_vel_C = FusionVectorHadamardProduct(P_vel_AB,GPS->K_vel);
    GPS->P_vel = (FusionVector){.axis = {
      .x = P_vel_AB.axis.x * P_vel_AB.axis.x + P_vel_C.axis.x,
      .y = P_vel_AB.axis.y * P_vel_AB.axis.y + P_vel_C.axis.y,
      .z = P_vel_AB.axis.z * P_vel_AB.axis.z + P_vel_C.axis.z,
    }};
    FusionVector VEL_kalman = FusionVectorHadamardProduct(GPS->K_vel, velocity_y); //x = K *y
*/
    //double denom = (1.0 - (ECC2 * pow(sin(GPS_kalman_rad.axis.x),2.0)));
    //denom = sqrt(denom*denom);
    //double Re = EARTH_RADIUS / sqrt(denom);
    //double Rn = EARTH_RADIUS*(1.0-ECC2) / denom*sqrt(denom);

    GPS_pos_ins_rad.axis.z = GPS_pos_rad.axis.z - GPS_kalman_rad.axis.z; 
    GPS_pos_ins_rad.axis.x = GPS_pos_rad.axis.x + (GPS_kalman_rad.axis.x + GPS->K.axis.x*GPS_error.axis.x)/ (Rew + GPS_pos_ins_rad.axis.z);
    GPS_pos_ins_rad.axis.y = GPS_pos_rad.axis.y + ((GPS_kalman_rad.axis.y + GPS->K.axis.y*GPS_error.axis.y) / (Rns + GPS_pos_ins_rad.axis.z)) / cos(GPS_pos_ins_rad.axis.x);
    //GPS_pos_ins_rad.axis.z -= GPS_kalman_rad.axis.z; 
    //GPS_pos_ins_rad.axis.x += (GPS_kalman_rad.axis.x + GPS->K.axis.x*GPS_error.axis.x)/ (Rew + GPS_pos_ins_rad.axis.z);
    //GPS_pos_ins_rad.axis.y += ((GPS_kalman_rad.axis.y + GPS->K.axis.y*GPS_error.axis.y) / (Rns + GPS_pos_ins_rad.axis.z)) / cos(GPS_pos_ins_rad.axis.x);

    GPS->location_ins.axis.x = FusionRadiansToDegrees(GPS_pos_ins_rad.axis.x);
    GPS->location_ins.axis.y = FusionRadiansToDegrees(GPS_pos_ins_rad.axis.y);
    GPS->location_ins.axis.z = GPS_pos_ins_rad.axis.z;
    GPS->location = pos;
    GPS->location_ahrs = GPS->location_ins;

    //GPS->velocity_ins = FusionVectorAdd(vel,VEL_kalman);
  }
}

/**
 * @brief Returns the GPS algorithm flags.
 * @param GPS GPS algorithm structure.
 * @return GPS algorithm flags.
 */
FusionGPSFlags FusionGPSGetFlags(const FusionGPS *const GPS) {
    const unsigned int warningTimeout = GPS->settings.rejectionTimeout / 4;
    const FusionGPSFlags flags = {
            .initialising = GPS->initialising,
            .locationRejectionWarning = GPS->locationRejectionTimer > warningTimeout,
            .locationRejectionTimeout = GPS->locationRejectionTimeout,
            .velocityRejectionWarning = GPS->velocityRejectionTimer > warningTimeout,
            .velocityRejectionTimeout = GPS->velocityRejectionTimeout,
    };
    return flags;
}

/**
 * @brief This function calculates the ECEF Coordinate given the Latitude, Longitude and Altitude.
 * @param pos Latitude, Longitude and Altitude vector data structure.
 * @return ECEF vector.
 */
FusionVectorDouble FusionGPSpos2ecef(const FusionVector pos) {
#define P pos.axis
  //double Rew, denom;

  //denom = (1.0 - (ECC2 * pow(sin(P.x),2.0)));
  //denom = sqrt(denom*denom);

  //Rew = EARTH_RADIUS / sqrt(denom);

  const FusionVectorDouble ecef = {.axis = {
    .x = (Rew + P.z) * cos(P.x) * cos(P.y),
    .y = (Rew + P.z) * cos(P.x) * sin(P.y),
    .z = (Rew * (1.0 - ECC2) + P.z) * sin(P.x),
  }};
  return ecef;
#undef P
}

/**
 * @brief This function converts a vector in ecef to ned coordinate centered at pos_ref.
 * @param ecef vector in ecef.
 * @param pos_ref Latitude, Longitude and Altitude reference vector data structure.
 * @return vector ned.
 */
FusionVector FusionGPSecef2ned(FusionVectorDouble ecef,FusionVector pos_ref) {
#define E ecef.axis
#define P pos_ref.axis
  const FusionVector ned = {.axis = {
    .x = -sin(P.x)*cos(P.y)*E.x-sin(P.x)*sin(P.y)*E.y+cos(P.x)*E.z,
    .y = -sin(P.y)*E.x + cos(P.y)*E.y,
    .z = -cos(P.x)*cos(P.y)*E.x-cos(P.x)*sin(P.y)*E.y-sin(P.x)*E.z
    }};
  return ned;
#undef E
#undef P
}

/**
 * @brief This function calculates the rate of change of latitude, longitude, and altitude.
 * @param vel Velocity vector in NED.
 * @param pos Latitude, Longitude and Altitude reference vector data structure.
 * @return vector rate of change.
 */
FusionVectorDouble FusionGPSposrate(FusionVector vel,FusionVector pos) {
#define V vel.axis
#define P pos.axis
  //double Rew, Rns, denom;
  
  //denom = (1.0 - (ECC2 * pow(sin(P.x),2.0)));
  //denom = sqrt(denom*denom);

  //Rew = EARTH_RADIUS / sqrt(denom);
  //Rns = EARTH_RADIUS*(1.0-ECC2) / denom*sqrt(denom);

  const FusionVectorDouble pos_dot = {.axis = {
    .x = V.x/(Rns + P.z),
    .y = V.y/((Rew + P.z)*cos(P.x)),
    .z = -V.z
  }};
  return pos_dot;
#undef V
#undef P
}