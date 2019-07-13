#ifndef Parameters_h
#define Parameters_h

const float m = 0.03f;
const float I_xx = 1.6f*pow(10.0f,-5);
const float I_yy = 1.6f*pow(10.0f,-5);
const float I_zz = 2.9f*pow(10.0f,-5);

const float g = 9.81f;

const float phi_kp = 240.3f;//100.0f
const float phi_kd = 26.7f;//24.0f
const float theta_kp = 240.3f;//100.0f
const float theta_kd = 26.7f;//24.0f
const float psi_kp = 60.1f;//50.0f
const float psi_kd = 13.3f;//12.0f
const float x_kp = 1.28f;//1.28f;1.35
const float x_kd = 2.5f;//1.6f;
const float y_kp = 1.28f;//1.28f;1.35
const float y_kd = 2.5f;//1.6f;
const float z_kp = 5.41f;//32.0f;
const float z_kd = 4.0f;//10.0f;

const float dt = 0.002f;
const float dt_range = 0.05f;
const float dt_flow = 0.002f;

const float pi = 3.14159265f;
const float sigma = 0.001827923976f/dt_flow;

const float rho_att = 0.01f; //0.05f
const float rho_vert_corr = 0.3f; //0.5f
const float rho_horiz_corr = 0.3f; //0.3f

const float alpha = 1.145f*pow(10.0f,-7);
const float beta = 1.001f*pow(10.0f,-9);
const float kl = 2.1f*pow(10.0f,-8);
const float kd = 1.52f*pow(10.0f,-10);
const float l = 33.0f*pow(10.0f,-3);

#endif