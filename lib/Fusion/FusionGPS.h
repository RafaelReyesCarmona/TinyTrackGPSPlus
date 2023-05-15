/**
 * @file FusionGPS.h
 * @author Rafael Reyes
 * @brief Algorithm to combine GPS data with AHRS.
 */

#ifndef FUSION_GPS_H
#define FUSION_GPS_H

//------------------------------------------------------------------------------
// Includes

#include "FusionConvention.h"
#include "FusionMath.h"
#include <stdbool.h>

//------------------------------------------------------------------------------
// Definitions

/**
 * @brief GPS algorithm settings.
 */
typedef struct {
    FusionConvention convention;
    float gain;
    float locationRejection;
    float velocityRejection;
    unsigned int rejectionTimeout;
} FusionGPSSettings;

/**
 * @brief GPS algorithm structure.  Structure members are used internally and
 * must not be accessed by the application.
 */
typedef struct {
    FusionGPSSettings settings;
    bool initialising;
    FusionVectorDouble location_ins;
    FusionVectorDouble location;
    FusionVector velocity_ins;
    FusionVector velocity;
    FusionVector K;
    FusionVector P;
    FusionVector K_vel;
    FusionVector P_vel;
    FusionVectorDouble dx;
    FusionVectorDouble dxd;
    FusionQuaternion quaternium;
    FusionVector angular;
    bool locationIgnored;
    unsigned int locationRejectionTimer;
    bool locationRejectionTimeout;
    bool velocityIgnored;
    unsigned int velocityRejectionTimer;
    bool velocityRejectionTimeout;
} FusionGPS;

/**
 * @brief GPS algorithm internal states.
 */
typedef struct {
    float locationError;
    bool locationIgnored;
    float locationRejectionTimer;
    float velocityError;
    bool velocityIgnored;
    float velocityRejectionTimer;
} FusionGPSInternalStates;

/**
 * @brief GPS algorithm flags.
 */
typedef struct {
    bool initialising;
    bool locationRejectionWarning;
    bool locationRejectionTimeout;
    bool velocityRejectionWarning;
    bool velocityRejectionTimeout;
} FusionGPSFlags;

//------------------------------------------------------------------------------
// Function declarations

void FusionGPSInitialise(FusionGPS *const GPS);

void FusionGPSReset(FusionGPS *const GPS);

void FusionGPSSetSettings(FusionGPS *const GPS, const FusionGPSSettings *const settings);

void FusionGPSAHRSUpdate(FusionGPS *const GPS, const FusionQuaternion quaternium, const FusionVector accel, const float deltaTime);

void FusionGPSUpdate(FusionGPS *const GPS, const FusionVectorDouble pos, const FusionVector vel, const float deltaTime);

FusionGPSFlags FusionGPSGetFlags(const FusionGPS *const GPS);

FusionVectorDouble FusionGPSpos2ecef(const FusionVector pos);

FusionVector FusionGPSecef2ned(FusionVectorDouble ecef,FusionVector pos_ref);

FusionVectorDouble FusionGPSposrate(FusionVector vel,FusionVector pos);

#endif

//------------------------------------------------------------------------------
// End of file