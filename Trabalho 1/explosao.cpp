#include "explosao.h"
#include <GL/glut.h>
#include <iostream>
#include <math.h>

explosao::explosao(float x, float y, float initx, float inity,int vel,int alvo)
{
    this->x=x;
    this->y=y;
    this->raio=0;
    this->linex=initx;
    this->liney=inity;
    this->initx=initx;
    this->inity=inity;
    this->vel = vel;
    this->alvo = alvo;
    dx=sqrt(pow((linex-x),2))/vel;
    dy=sqrt(pow((liney-y),2))/vel;
}

void explosao::desenhar()
{
        glPushMatrix();
        if(cont<vel){
        if(linex<x)linex+=dx;//*dt*1000;
        if(linex>x)linex-=dx;//*dt*1000;
        if(liney<y)liney+=dy;//*dt*1000;
        if(liney>y)liney-=dy;//*dt*1000;
        glColor3f(0.0, 0.0,1.0);
        glBegin(GL_LINES);
            glVertex2f(linex, liney);
            glVertex2f(initx, inity);
        glEnd();
        cont++;
        tempo=0;
        }else{
        colide=1;
        glColor3f(cor, 0,0);
        glTranslatef(this->x, this->y, 0.0);
        glutSolidSphere(raio, 20, 2);
        raio+=2.5*dt;
        cor*=0.9999;
        if(!falha){
            destruiu=true;
        }
        }
        glPopMatrix();
}
