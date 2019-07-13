#ifndef Mixer_h
#define Mixer_h

#include "mbed.h"
#include "Parameters.h"

class Mixer
{
    public:
        // Class constructor
        Mixer();
        // Actuate motors with the desired force (N) and torques (N.m)
        void actuate( float ft , float tau_phi , float tau_theta , float tau_psi );
    private:
        // Motors PWM outputs
        PwmOut motor0, motor1, motor2, motor3;
        // Angular velocities ( rad /s)
        float omega0, omega1, omega2, omega3;
        // Converts desired force (N) and torques (N.m) to angular velocities ( rad/s)
        void ft_to_omega( float ft, float tau_phi, float tau_theta, float tau_psi );
        // Converts desired angular velocity (rad/s) to PWM signal
        float omega_to_pwm( float omega );
};

#endif