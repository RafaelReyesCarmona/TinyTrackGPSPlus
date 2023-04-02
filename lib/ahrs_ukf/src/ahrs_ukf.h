#ifndef AHRS_UKF_H
#define AHRS_UKF_H

#include <Wire.h>
#include <elapsedMillis.h>
#include "konfig.h"
#include "matrix.h"
#include "ukf.h"
//#include "simple_mpu9250.h"

/* ================================================= RLS Variables/function declaration ================================================= */
float_prec  RLS_lambda = 0.999; /* Forgetting factor */
Matrix RLS_theta(4,1);          /* The variables we want to indentify */
Matrix RLS_P(4,4);              /* Inverse of correction estimation */
Matrix RLS_in(4,1);             /* Input data */
Matrix RLS_out(1,1);            /* Output data */
Matrix RLS_gain(4,1);           /* RLS gain */
uint32_t RLS_u32iterData = 0;   /* To track how much data we take */


/* ================================================= UKF Variables/function declaration ================================================= */
/* UKF initialization constant */
#define P_INIT       (10.)
#define Rv_INIT      (1e-6)
#define Rn_INIT_ACC  (0.0015/10.)
#define Rn_INIT_MAG  (0.0015/10.)
/* P(k=0) variable --------------------------------------------------------------------------------------------------------- */
float_prec UKF_PINIT_data[SS_X_LEN*SS_X_LEN] = {P_INIT, 0,      0,      0,
                                                0,      P_INIT, 0,      0,
                                                0,      0,      P_INIT, 0,
                                                0,      0,      0,      P_INIT};
Matrix UKF_PINIT(SS_X_LEN, SS_X_LEN, UKF_PINIT_data);
/* Q constant -------------------------------------------------------------------------------------------------------------- */
float_prec UKF_Rv_data[SS_X_LEN*SS_X_LEN] = {Rv_INIT, 0,       0,       0,
                                             0,       Rv_INIT, 0,       0,
                                             0,       0,       Rv_INIT, 0,
                                             0,       0,       0,       Rv_INIT};
Matrix UKF_Rv(SS_X_LEN, SS_X_LEN, UKF_Rv_data);
/* R constant -------------------------------------------------------------------------------------------------------------- */
float_prec UKF_Rn_data[SS_Z_LEN*SS_Z_LEN] = {Rn_INIT_ACC, 0,           0,           0,           0,           0,
                                             0,           Rn_INIT_ACC, 0,           0,           0,           0,
                                             0,           0,           Rn_INIT_ACC, 0,           0,           0,
                                             0,           0,           0,           Rn_INIT_MAG, 0,           0,
                                             0,           0,           0,           0,           Rn_INIT_MAG, 0,
                                             0,           0,           0,           0,           0,           Rn_INIT_MAG};
Matrix UKF_Rn(SS_Z_LEN, SS_Z_LEN, UKF_Rn_data);
/* Nonlinear & linearization function -------------------------------------------------------------------------------------- */
bool Main_bUpdateNonlinearX(Matrix &X_Next, Matrix &X, Matrix &U);
bool Main_bUpdateNonlinearY(Matrix &Y, Matrix &X, Matrix &U);
/* UKF variables ----------------------------------------------------------------------------------------------------------- */
Matrix quaternionData(SS_X_LEN, 1);
Matrix Y(SS_Z_LEN, 1);
Matrix U(SS_U_LEN, 1);
UKF UKF_IMU(quaternionData, UKF_PINIT, UKF_Rv, UKF_Rn, Main_bUpdateNonlinearX, Main_bUpdateNonlinearY);

/* =============================================== Sharing Variables/function declaration =============================================== */
/* Gravity vector constant (align with global Z-axis) */
#define IMU_ACC_Z0          (1)

/* Magnetic vector constant (align with local magnetic vector) */
float_prec IMU_MAG_B0_data[3] = {cos(0), sin(0), 0.000000};
Matrix IMU_MAG_B0(3, 1, IMU_MAG_B0_data);

bool Main_bUpdateNonlinearX(Matrix &X_Next, Matrix &X, Matrix &U)
{
    /* Insert the nonlinear update transformation here
     *          x(k+1) = f[x(k), u(k)]
     *
     * The quaternion update function:
     *  q0_dot = 1/2. * (  0   - p*q1 - q*q2 - r*q3)
     *  q1_dot = 1/2. * ( p*q0 +   0  + r*q2 - q*q3)
     *  q2_dot = 1/2. * ( q*q0 - r*q1 +  0   + p*q3)
     *  q3_dot = 1/2. * ( r*q0 + q*q1 - p*q2 +  0  )
     * 
     * Euler method for integration:
     *  q0 = q0 + q0_dot * dT;
     *  q1 = q1 + q1_dot * dT;
     *  q2 = q2 + q2_dot * dT;
     *  q3 = q3 + q3_dot * dT;
     */
    float_prec q0, q1, q2, q3;
    float_prec p, q, r;
    
    q0 = X[0][0];
    q1 = X[1][0];
    q2 = X[2][0];
    q3 = X[3][0];
    
    p = U[0][0];
    q = U[1][0];
    r = U[2][0];
    
    X_Next[0][0] = (0.5 * (+0.00 -p*q1 -q*q2 -r*q3))*SS_DT + q0;
    X_Next[1][0] = (0.5 * (+p*q0 +0.00 +r*q2 -q*q3))*SS_DT + q1;
    X_Next[2][0] = (0.5 * (+q*q0 -r*q1 +0.00 +p*q3))*SS_DT + q2;
    X_Next[3][0] = (0.5 * (+r*q0 +q*q1 -p*q2 +0.00))*SS_DT + q3;
    
    
    /* ======= Additional ad-hoc quaternion normalization to make sure the quaternion is a unit vector (i.e. ||q|| = 1) ======= */
    if (!X_Next.bNormVector()) {
        /* System error, return false so we can reset the UKF */
        return false;
    }
    
    return true;
}

bool Main_bUpdateNonlinearY(Matrix &Y, Matrix &X, Matrix &U)
{
    /* Insert the nonlinear measurement transformation here
     *          y(k)   = h[x(k), u(k)]
     *
     * The measurement output is the gravitational and magnetic projection to the body
     *     DCM     = [(+(q0**2)+(q1**2)-(q2**2)-(q3**2)),                        2*(q1*q2+q0*q3),                        2*(q1*q3-q0*q2)]
     *               [                   2*(q1*q2-q0*q3),     (+(q0**2)-(q1**2)+(q2**2)-(q3**2)),                        2*(q2*q3+q0*q1)]
     *               [                   2*(q1*q3+q0*q2),                        2*(q2*q3-q0*q1),     (+(q0**2)-(q1**2)-(q2**2)+(q3**2))]
     * 
     *  G_proj_sens = DCM * [0 0 1]             --> Gravitational projection to the accelerometer sensor
     *  M_proj_sens = DCM * [Mx My Mz]          --> (Earth) magnetic projection to the magnetometer sensor
     */
    float_prec q0, q1, q2, q3;
    float_prec q0_2, q1_2, q2_2, q3_2;

    q0 = X[0][0];
    q1 = X[1][0];
    q2 = X[2][0];
    q3 = X[3][0];

    q0_2 = q0 * q0;
    q1_2 = q1 * q1;
    q2_2 = q2 * q2;
    q3_2 = q3 * q3;
    
    Y[0][0] = (2*q1*q3 -2*q0*q2) * IMU_ACC_Z0;

    Y[1][0] = (2*q2*q3 +2*q0*q1) * IMU_ACC_Z0;

    Y[2][0] = (+(q0_2) -(q1_2) -(q2_2) +(q3_2)) * IMU_ACC_Z0;
    
    Y[3][0] = (+(q0_2)+(q1_2)-(q2_2)-(q3_2)) * IMU_MAG_B0[0][0]
             +(2*(q1*q2+q0*q3)) * IMU_MAG_B0[1][0]
             +(2*(q1*q3-q0*q2)) * IMU_MAG_B0[2][0];

    Y[4][0] = (2*(q1*q2-q0*q3)) * IMU_MAG_B0[0][0]
             +(+(q0_2)-(q1_2)+(q2_2)-(q3_2)) * IMU_MAG_B0[1][0]
             +(2*(q2*q3+q0*q1)) * IMU_MAG_B0[2][0];

    Y[5][0] = (2*(q1*q3+q0*q2)) * IMU_MAG_B0[0][0]
             +(2*(q2*q3-q0*q1)) * IMU_MAG_B0[1][0]
             +(+(q0_2)-(q1_2)-(q2_2)+(q3_2)) * IMU_MAG_B0[2][0];
    return true;
}


#endif