#include "mbed.h"
#include "Parameters.h"
#include "Mixer.h"

// Class constructor
Mixer::Mixer() : motor0(PA_1), motor1(PB_11), motor2(PA_15), motor3(PB_9_ALT1)
{
}

// Actuate motors with the desired force (N) and torques (N.m)
void Mixer::actuate( float ft , float tau_phi , float tau_theta , float tau_psi )
{
    ft_to_omega(ft,tau_phi,tau_theta,tau_psi);
    motor0 = omega_to_pwm(omega0);
    motor1 = omega_to_pwm(omega1);
    motor2 = omega_to_pwm(omega2);
    motor3 = omega_to_pwm(omega3);
}

// Converts desired force (N) and torques (N.m) to angular velocities ( rad /s)
void Mixer::ft_to_omega( float ft , float tau_phi , float tau_theta , float tau_psi )
{
    float a1 = (1.0f/(4.0f*kl))*ft;
    float a2 = (1.0f/(4.0f*kl*l))*tau_phi;
    float a3 = (1.0f/(4.0f*kl*l))*tau_theta;
    float a4 = (1.0f/(4.0f*kd))*tau_psi;
    
    float omega02 = a1 - a2 - a3 - a4;
    float omega12 = a1 - a2 + a3 + a4;
    float omega22 = a1 + a2 + a3 - a4;
    float omega32 = a1 + a2 - a3 + a4;
    
    if (omega02 < 0.0f){
        omega02 = 0.0f;
    }
    if (omega12 < 0.0f){
        omega12 = 0.0f;
    }
    if (omega22 < 0.0f){
        omega22 = 0.0f;
    }
    if (omega32 < 0.0f){
        omega32 = 0.0f;
    }
    
    omega0 = sqrt(omega02);
    omega1 = sqrt(omega12);
    omega2 = sqrt(omega22);
    omega3 = sqrt(omega32);
}

// Converts desired angular velocity (rad/s) to PWM signal
float Mixer::omega_to_pwm( float omega )
{
    float pwm = alpha*pow(omega,2) + beta*omega;
    return pwm;
}