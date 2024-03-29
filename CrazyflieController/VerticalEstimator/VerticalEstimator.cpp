#include "mbed.h"
#include "VerticalEstimator.h"

// Class constructor
VerticalEstimator::VerticalEstimator() : range(PB_7,PB_6)
{
    z = 0.0f;
    w = 0.0f;
    z_m_last = 0.0f;
}
// Initialize class
void VerticalEstimator::init()
{
    range.init();
}
// Predict vertical position and velocity from model
void VerticalEstimator::predict()
{
    z = z + w*dt;
}
// Correct vertical position and velocity with measurement
void VerticalEstimator::correct(float phi,float theta)
{
    range.read();
    float z_m = range.z*cos(phi)*cos(theta);
    float w_m = (z_m - z_m_last)/dt_range;
    
    z = (1.0f - rho_vert_corr)*z + rho_vert_corr*z_m;
    w = (1.0f - rho_vert_corr)*w + rho_vert_corr*w_m;
    
    z_m_last = z_m;
}