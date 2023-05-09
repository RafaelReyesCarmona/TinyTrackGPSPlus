/**
 * @file FusionCompass.c
 * @author Seb Madgwick
 * @brief Tilt-compensated compass to calculate the magnetic heading using
 * accelerometer and magnetometer measurements.
 */

//------------------------------------------------------------------------------
// Includes

#include "FusionAxes.h"
#include "FusionCompass.h"
#include <math.h> // atan2f


/* Apparently M_PI isn't available in all environments. */
#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif
//------------------------------------------------------------------------------
// Functions

/**
 * @brief Calculates the magnetic heading.
 * @param convention Earth axes convention.
 * @param accelerometer Accelerometer measurement in any calibrated units.
 * @param magnetometer Magnetometer measurement in any calibrated units.
 * @return Heading angle in degrees.
 */
float FusionCompassCalculateHeading(const FusionConvention convention, const FusionVector accelerometer, const FusionVector magnetometer) {
    switch (convention) {
        case FusionConventionNwu: {
            const FusionVector west = FusionVectorNormalise(FusionVectorCrossProduct(accelerometer, magnetometer));
            const FusionVector north = FusionVectorNormalise(FusionVectorCrossProduct(west, accelerometer));
            return FusionRadiansToDegrees(atan2f(west.axis.x, north.axis.x));
        }
        case FusionConventionEnu: {
            const FusionVector west = FusionVectorNormalise(FusionVectorCrossProduct(accelerometer, magnetometer));
            const FusionVector north = FusionVectorNormalise(FusionVectorCrossProduct(west, accelerometer));
            const FusionVector east = FusionVectorMultiplyScalar(west, -1.0f);
            return FusionRadiansToDegrees(atan2f(north.axis.x, east.axis.x));
        }
        case FusionConventionNed: {
            const FusionVector up = FusionVectorMultiplyScalar(accelerometer, -1.0f);
            const FusionVector west = FusionVectorNormalise(FusionVectorCrossProduct(up, magnetometer));
            const FusionVector north = FusionVectorNormalise(FusionVectorCrossProduct(west, up));
            return FusionRadiansToDegrees(atan2f(west.axis.x, north.axis.x));
        }
    }
	return 0; // avoid compiler warning
}

float FusionCompassCalculateHeading2(const FusionVector magnetometer) {
#define M magnetometer.axis
	float a = FusionRadiansToDegrees(atan2( M.y, M.x ));
	return a < 0 ? 360 + a : a;
#undef M
}

float FusionCompassCalculateBearing(const FusionEuler euler, const FusionVector magnetometer) {
#define E euler.angle
#define M magnetometer.axis
    // Precompute the tilt compensation parameters to improve readability.
    float phi = FusionDegreesToRadians(E.roll);
    float theta = FusionDegreesToRadians(E.pitch);

    // Precompute cos and sin of pitch and roll angles to make the calculation a little more efficient.
    float sinPhi = sin(phi);
    float cosPhi = cos(phi);
    float sinTheta = sin(theta);
    float cosTheta = cos(theta);

    // Calculate the tilt compensated bearing, and convert to degrees.
    float bearing = (360*atan2(M.x*cosTheta + M.y*sinTheta*sinPhi + M.z*sinTheta*cosPhi, M.z*sinPhi - M.y*cosPhi)) / (2*M_PI);

    // Handle the 90 degree offset caused by the NORTH_EAST_DOWN based calculation.
    bearing = 90 - bearing;

    // Ensure the calculated bearing is in the 0..359 degree range.
    if (bearing < 0)
        bearing += 360.0f;

    return (int) (bearing);
#undef E
#undef M
}
//------------------------------------------------------------------------------
// End of file
