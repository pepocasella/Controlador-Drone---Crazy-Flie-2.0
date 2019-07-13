#include "mbed.h"
#include "CrazyflieController.h"

AttitudeEstimator att_est;
AttitudeController att_cont;
VerticalEstimator ver_est;
VerticalController ver_cont;
HorizontalEstimator hor_est;
HorizontalController hor_cont;
Mixer mixer;

// Tickers
Timer tim;
Ticker tic;
Ticker tic_range;
Ticker tic_flow;

// Interrupt flags
bool flag = false;
bool flag_range = false;
bool flag_flow = false;

// Callback function
void callback()
{
    flag = true;
}

// Callback function ( range correct )
void callback_range()
{
    flag_range = true;
}

// Callback function ( flow correct )
void callback_flow()
{
    flag_flow = true;
}

int main()
{
    float x_r = 0.0f;
    float y_r = 0.0f;
    float z_r = 1.0f;
    float psi_r = 0.0f;
    
    // Wait 5s for safety
    wait(5);
    
    // Initialize estimators objects
    att_est.init();
    ver_est.init();
    hor_est.init();
    
    // Initialize interrupts
    tic.attach(&callback,dt);
    tic_range.attach(&callback_range,dt_range);
    tic_flow.attach(&callback_flow,dt_flow);
    
    tim.start();
    
    float qpi = pi/4.0f;
    float piq = 5.0f*pi;
    
    while(abs(att_est.phi) <= qpi && abs(att_est.theta) <= qpi && abs(att_est.p) <= piq && abs(att_est.q) <= piq && abs(att_est.r) <= piq)
    {
        /*if(tim.read() >= 15.0f)
        {
            z_r = 1.0f + 0.3f*sin(tim.read());
        }*/
        
        if(flag)
        {
            flag = false;
            att_est.estimate();
            ver_est.predict();
            hor_est.predict();
            
            if(ver_est.z >= 0.1f)
            {
                hor_cont.control(x_r, y_r, hor_est.x, hor_est.y, hor_est.u, hor_est.v);
            }
            ver_cont.control(z_r, ver_est.z, ver_est.w);
            att_cont.control(hor_cont.phi_r, hor_cont.theta_r, psi_r, att_est.phi, att_est.theta, att_est.psi, att_est.p, att_est.q, att_est.r);
            mixer.actuate(ver_cont.f_t/(cos(att_est.phi)*cos(att_est.theta)), att_cont.tau_phi, att_cont.tau_theta, att_cont.tau_psi);
        }
        // Correct vertical estimation and print values
        if(flag_range)
        {
            flag_range = false;
            ver_est.correct(att_est.phi,att_est.theta);
        }
        // Correct horizontal estimation
        if ( flag_flow )
        {
            flag_flow = false;
            if(ver_est.z >= 0.1f)
            {
                hor_est.correct(att_est.phi , att_est.theta , att_est.p, att_est.q, ver_est.z);
            }
        }
    }
    mixer.actuate(0.0f,0.0f,0.0f,0.0f);
    while(1);
}