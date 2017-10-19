#ifndef CAMERA_H
#define CAMERA_H

#include "math.h"
#include <GL/glut.h>
#include <iostream>

#define M_PI 3.14
class Camera
{
    public:
        Camera();
        virtual ~Camera();
        //controle da camera
        void init();
        void atualiza();
        void setPos(float x, float y, float z);
        void getPos(float &x, float &y, float &z);
        void getDirVector(float &x, float &y, float &z);
        void setYaw(float angulo);
        void setPitch(float angulo);

        //navegacao
        void move(float incr, bool flyMode = true);
        void strafe(float incr);
        void fly(float incr);
        void rotacionaYaw(float angulo);
        void rotacionaPitch(float angulo);
    private:
        float pX, pY, pZ; //posicao
        float pdX, pdY, pdZ; //vetor direcao para o looking at
        float yaw, pitch; //angulos de rotacao
        float strafe_lx, strafe_lz; //sempre 90 graus


};

#endif // CAMERA_H
