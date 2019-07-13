#ifndef HorizontalController_h
#define HorizontalController_h

#include "mbed.h"
#include "Parameters.h"

class HorizontalController
{
    public:
        
        HorizontalController();
        
        void control(float x_r, float y_r, float x, float y, float u, float v);
        
        float phi_r, theta_r;
    
    private:
        
        float control_single(float pos_r, float pos, float vel, float kp, float kd);
};

#endif