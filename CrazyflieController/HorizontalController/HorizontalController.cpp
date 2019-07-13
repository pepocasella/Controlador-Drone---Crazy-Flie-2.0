#include "mbed.h"
#include "HorizontalController.h"

HorizontalController::HorizontalController()
{
    phi_r = 0.0f;
    theta_r = 0.0f;
}

void HorizontalController::control(float x_r, float y_r, float x, float y, float u, float v)
{
    phi_r = control_single(y_r, y, v, y_kp, y_kd)/(-g);
    theta_r = control_single(x_r, x, u, x_kp, x_kd)/g;
}

float HorizontalController::control_single(float pos_r, float pos, float vel, float kp, float kd)
{
    return kp*(pos_r - pos) - kd*vel;
}