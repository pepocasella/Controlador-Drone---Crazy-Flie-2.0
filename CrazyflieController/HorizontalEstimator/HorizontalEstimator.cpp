#include "mbed.h"
#include "HorizontalEstimator.h"

// Class constructor
HorizontalEstimator::HorizontalEstimator():flow(PA_7,PA_6,PA_5,PB_4)
{
    x = 0.0f;
    y = 0.0f;
    u = 0.0f;
    v = 0.0f;
    x_m_last = 0.0f;
    y_m_last = 0.0f;
}
// Initialize class
void HorizontalEstimator::init()
{
    flow.init();
}
// Predict horizontal position and velocity from model
void HorizontalEstimator::predict()
{
    x = x + u*dt;
    y = y + v*dt;
}
// Correct horizontal position and velocity with measurements
void HorizontalEstimator::correct(float phi,float theta,float p,float q,float z)
{
    float Cphi = cos(phi);
    float Ctheta = cos(theta);
    
    if( Cphi >= 0.7f && Ctheta >= 0.7f )
    {
        float d = z/(Cphi*Ctheta);
        
        flow.read();
        float u_m = (sigma*flow.x + q)*d;
        float v_m = (sigma*flow.y - p)*d;
        
        float x_m = x_m_last + u_m*dt_flow;
        float y_m = y_m_last + v_m*dt_flow;
        
        x = (1.0f - rho_horiz_corr)*x + rho_horiz_corr*x_m;
        y = (1.0f - rho_horiz_corr)*y + rho_horiz_corr*y_m;
        u = (1.0f - rho_horiz_corr)*u + rho_horiz_corr*u_m;
        v = (1.0f - rho_horiz_corr)*v + rho_horiz_corr*v_m;
        
        x_m_last = x_m;
        y_m_last = y_m;
    }
}
