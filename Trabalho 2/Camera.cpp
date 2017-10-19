#include "Camera.h"

Camera::Camera()
{
    init();
}

void Camera::init(){
    yaw = 0.0; //angulo inicial
    pitch = 0.0; //angulo inicial
    setPos(0, 0, 0) //posicao inicial
}
void Camera::atualiza(){
    pdX = cos(yaw)* cos(pitch);
    pdY = sin(pitch);
    pdZ = sin(yaw)*cos(pitch);
    strafe_lx = cos(yaw - M_PI);
    strafe_lz = sin(yaw - M_PI);
}
Camera::~Camera()
{
    //dtor
}
