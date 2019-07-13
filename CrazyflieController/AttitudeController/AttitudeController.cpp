#include "mbed.h"
#include "Parameters.h"
#include "AttitudeController.h"

// Class constructor
AttitudeController::AttitudeController()
{
}

// Control torques given reference angles and current angles and angular velocities
void AttitudeController::control( float phi_r , float theta_r , float psi_r , float phi, float theta , float psi , float p, float q, float r)
{
    tau_phi = single_axis_control(phi_r, phi, p, phi_kp, phi_kd, I_xx);
    tau_theta = single_axis_control(theta_r, theta, q, theta_kp, theta_kd, I_yy);
    tau_psi = single_axis_control(psi_r, psi, r, psi_kp, psi_kd, I_zz);
}
// Control torque of a single axis given reference angles and current angles and angular velocities ( with given gains and /or time constants and moments of inertia )
float AttitudeController::single_axis_control( float angle_r , float angle , float rate , float K_angle , float K_rate , float I)
{
    return I*(K_angle*(angle_r - angle) - K_rate*rate);
}