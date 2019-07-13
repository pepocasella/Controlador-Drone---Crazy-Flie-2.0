#include "mbed.h"
#include "Parameters.h"
#include "MPU9250.h"
#include "AttitudeEstimator.h"

// Class constructor
AttitudeEstimator::AttitudeEstimator() : imu(PC_9,PA_8)
{
}

// Initialize class
void AttitudeEstimator::init()
{
    imu.init();
    calibrate_gyro();
}

// Calibrates gyroscope by calculating angular velocity bias (rad/s)
void AttitudeEstimator::calibrate_gyro()
{
    for(int i=0;i<200;i++){
        imu.read();
        p_bias += imu.gx;
        q_bias += imu.gy;
        r_bias += imu.gz;
        wait_ms(dt);
    }
    p_bias /= 200.0f;
    q_bias /= 200.0f;
    r_bias /= 200.0f;
}

// Estimate Euler angles (rad) and angular velocity (rad/s)
void AttitudeEstimator::estimate()
{
    imu.read();
    
    estimate_accel();
    estimate_gyro();
    
    phi = rho_att*phi_accel + (1.0f - rho_att)*phi_gyro;
    theta = rho_att*theta_accel + (1.0f - rho_att)*theta_gyro;
    psi = psi_gyro;
}

// Estimate Euler angles (rad) from accelerometer data
void AttitudeEstimator::estimate_accel()
{
    phi_accel = atan2(-imu.ay,-imu.az);
    
    if(imu.az >= 0.0f){
        theta_accel = atan2(imu.ax,-sqrt(pow(imu.ay,2) + pow(imu.az,2)));
    }else{
        theta_accel = atan2(imu.ax,sqrt(pow(imu.ay,2) + pow(imu.az,2)));
    }
}

// Estimate Euler angles (rad) and angular velocities (rad/s) from gyroscope data
void AttitudeEstimator::estimate_gyro()
{
    p = imu.gx - p_bias;
    q = imu.gy - q_bias;
    r = imu.gz - r_bias;
    
    phi_gyro = phi + (p + sin(phi)*tan(theta)*q + cos(phi)*tan(theta)*r)*dt;
    theta_gyro = theta + (cos(phi)*q - sin(phi)*r)*dt;
    psi_gyro = psi + ((sin(phi)/cos(theta))*q + (cos(phi)/cos(theta))*r)*dt;
    
    if(phi_gyro > pi){
        phi_gyro -= 2.0f*pi;
    }
    if(theta_gyro > pi){
        theta_gyro -= 2.0f*pi;
    }
    if(psi_gyro > pi){
        psi_gyro -= 2.0f*pi;
    }
}