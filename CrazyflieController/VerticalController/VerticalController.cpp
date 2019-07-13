#include "mbed.h"
#include "VerticalController.h"

VerticalController::VerticalController()
{
    f_t = 0.0f;
}

void VerticalController::control(float z_r, float z, float w)
{
    f_t = m*( z_kp*( z_r - z ) - z_kd*w + g);
}