#ifndef AttitudeEstimator_h
#define AttitudeEstimator_h

#include "mbed.h"
#include "Parameters.h"
#include "MPU9250.h"

// Attitude estimator class
class AttitudeEstimator
{
    public:
        // Class constructor
        AttitudeEstimator();
        // Initialize class
        void init();
        // Estimate Euler angles (rad) and angular velocities (rad/s)
        void estimate();
        // Euler angles (rad)
        float phi, theta, psi;
        // Angular velocities (rad/s)
        float p, q, r;
    private:
        // IMU sensor object
        MPU9250 imu;
        // Calibrates gyroscope by calculating angular velocity bias (rad/s)
        void calibrate_gyro();
        // Estimate Euler angles (rad) from accelerometer data
        void estimate_accel();
        // Estimate Euler angles (rad) and angular velocities (rad/s) from gyroscope data
        void estimate_gyro();
        // Euler angles (rad) from accelerometer data
        float phi_accel, theta_accel;
        // Euler angles (rad) from gyroscope data
        float phi_gyro, theta_gyro, psi_gyro;
        // Angular velocities bias (rad/s)
        float p_bias, q_bias, r_bias;
};

#endif