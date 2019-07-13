#ifndef AttitudeController_h
#define AttitudeController_h

#include "mbed.h"
#include "Parameters.h"

class AttitudeController
{
    public:
        AttitudeController();
        
        void control(float phi_r, float theta_r, float psi_r, float phi, float theta, float psi, float p, float q, float r);
        
        float tau_phi, tau_theta, tau_psi;
    private:
        
        float single_axis_control(float angle_r, float angle, float rate, float K_angle, float K_rate, float I);
};

#endif