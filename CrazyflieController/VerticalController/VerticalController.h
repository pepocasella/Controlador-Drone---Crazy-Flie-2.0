#ifndef VerticalController_h
#define VerticalController_h

#include "mbed.h"
#include "Parameters.h"

class VerticalController 
{
    public:
        
        VerticalController();
        
        void control(float z_r, float z, float w);
        
        float f_t;
};

#endif