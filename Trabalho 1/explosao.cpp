#include "explosao.h"
#include <GL/glut.h>
#include <iostream>
#include <math.h>

explosao::explosao(float x, float y, float initx, float inity,int vel,int alvo)//instancia as variaveis
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
    dx=sqrt(pow((linex-x),2))/vel;//steps para chegar em x
    dy=sqrt(pow((liney-y),2))/vel;//steps para chegar em y
}

void explosao::desenhar()
{
        glPushMatrix();
        if(cont<vel){//increace the steps
        if(linex<x)linex+=dx;//*dt*1000;
        if(linex>x)linex-=dx;//*dt*1000;
        if(liney<y)liney+=dy;//*dt*1000;
        if(liney>y)liney-=dy;//*dt*1000;
        glColor3f(0.0, 0.0,1.0);
        glBegin(GL_LINES);//desenha o rastro (linha)
            glVertex2f(linex, liney);
            glVertex2f(initx, inity);
        glEnd();
        cont++;
        tempo=0;
        }else{
        colide=1;//se torna colidivel
        glColor3f(cor, 0,0);
        glTranslatef(this->x, this->y, 0.0);
        glutSolidSphere(raio, 20, 2);
        raio+=2.5*dt;//aumenta e diminui o raio
        cor*=0.9999;//vai escurecendo
        if(!falha){//se for atingido no ar
            destruiu=true;//foi destruido
        }
        }
        glPopMatrix();
}
