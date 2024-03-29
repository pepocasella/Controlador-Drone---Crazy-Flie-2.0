#ifndef VerticalEstimator_h
#define VerticalEstimator_h

#include "mbed.h"
#include "Parameters.h"
#include "VL53L0X.h"

// Vertical estimator class
class VerticalEstimator
{
    public:
        // Class constructor
        VerticalEstimator();
        // Initialize class
        void init();
        // Predict vertical position and velocity from model
        void predict();
        // Correct vertical position and velocity with measurement
        void correct(float phi,float theta);
        // Vertical position (m) and velocity (m/s) estimation
        float z,w;
    private:
        // Range sensor object
        VL53L0X range;
        // Last vertical position (m) measurement
        float z_m_last;
};

#endif