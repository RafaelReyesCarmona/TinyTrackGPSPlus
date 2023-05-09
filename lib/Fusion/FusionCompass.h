/**
 * @file FusionCompass.h
 * @author Seb Madgwick
 * @brief Tilt-compensated compass to calculate the magnetic heading using
 * accelerometer and magnetometer measurements.
 */

#ifndef FUSION_COMPASS_H
#define FUSION_COMPASS_H

//------------------------------------------------------------------------------
// Includes

#include "FusionConvention.h"
#include "FusionMath.h"

//------------------------------------------------------------------------------
// Function declarations

float FusionCompassCalculateHeading(const FusionConvention convention, const FusionVector accelerometer, const FusionVector magnetometer);

float FusionCompassCalculateHeading2(const FusionVector magnetometer);

float FusionCompassCalculateBearing(const FusionEuler euler, const FusionVector magnetometer);

#endif

//------------------------------------------------------------------------------
// End of file
