#include "explosao.h"
#include <GL/glut.h>
#include <iostream>
#include <math.h>

explosao::explosao(float x, float y, float initx, float inity)
{
    this->x=x;
    this->y=y;
    this->raio=0;
    this->linex=initx;
    this->liney=inity;
    this->initx=initx;
    this->inity=inity;
    dx=sqrt(pow((linex-x),2))/vel;
    dy=sqrt(pow((liney-y),2))/vel;
}

void explosao::desenhar()
{
        glPushMatrix();
        if(cont<vel){
        if(linex<x)linex+=dx;
        if(linex>x)linex-=dx;
        if(liney<y)liney+=dy;
        if(liney>y)liney-=dy;
        glColor3f(0.0, 0.0,1.0);
        glBegin(GL_LINES);
            glVertex2f(linex, liney);
            glVertex2f(initx, inity);
        glEnd();
        cont++;
        }else{
        glColor3f(cor, 0,0);
        glTranslatef(this->x, this->y, 0.0);
        glutSolidSphere(raio, 100, 100);
        raio=tempo;
        cor*=0.999;
        }
        glPopMatrix();
}
