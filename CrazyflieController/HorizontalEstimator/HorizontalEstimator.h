#ifndef HorizontalEstimator_h
#define HorizontalEstimator_h

#include "mbed.h"
#include "Parameters.h"
#include "PMW3901.h"

// Horizontal estimator class
class HorizontalEstimator
{
    public:
        // Class constructor
        HorizontalEstimator();
        // Initialize class
        void init();
        // Predict horizontal position and velocity from model
        void predict();
        // Correct horizontal position and velocity with measurements
        void correct(float phi,float theta,float p,float q,float z);
        // Horizontal positions (m) and velocities (m/s) estimations
        float x, y, u, v;
    private:
        // Flow sensor object
        PMW3901 flow;
        // Last horizontal positions (m) measurements
        float x_m_last, y_m_last;
};

#endif