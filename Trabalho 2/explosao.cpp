#include "explosao.h"
#include <GL/glut.h>
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
        glDisable(GL_LIGHTING);
        glBegin(GL_LINES);//desenha o rastro (linha)
            glVertex2f(linex, liney);
            glVertex2f(initx, inity);
        glEnd();
        glEnable(GL_LIGHTING);
        float m = (inity-liney)/(initx-linex);
        m=atan(m)*180/3.14;
        int inv = m/fabs(m);
        int um=1;
        if(liney<inity)
            um*=-1;
        inv*=um;
        glPushMatrix();
        setMaterial_missil();
        glTranslatef(linex,liney,-735);
        glRotatef(90,1,0,0);
        glRotatef(m+(90*inv),0,1,0);
        glScalef(0.1,0.1,0.1);
        desenhaFace(missile);
        glPopMatrix();
        cont++;
        tempo=0;
        }else{
        colide=1;//se torna colidivel
        setMaterial_explosao();
        glTranslatef(this->x, this->y, -735.0);
        glutSolidSphere(raio, 30, 30);
        raio+=2.5*dt;//aumenta e diminui o raio
        cor*=0.9999;//vai escurecendo
        if(!falha){//se for atingido no ar
            destruiu=true;//foi destruido
        }
        }
        glPopMatrix();
}

void explosao::desenhaFace(Modelo *m)
{

    glColor3f(1.0, 1.0, 1.0);
    double **vertices = m->getVertices();
    int **faces = m->getFaces();
    double **normal = m->getNormal();
    for (int i = 0; i < m->getTamFaces(); i++)
    {
        glFrontFace(GL_CCW);
        //setMaterial();
        glBegin(GL_POLYGON);
        glNormal3f(normal[i][0], normal[i][1], normal[i][2]);
        //cout << "normais: " << normal[i][0] << " " << normal[i][1] << " " << normal[i][2] << endl;
        for (int k = 1; k < 4; k++)
            glVertex3f(vertices[faces[i][k]][0], vertices[faces[i][k]][1], vertices[faces[i][k]][2]);
        glEnd();
    }
}


void explosao::setMaterial_missil(void)
{
    //silver
    GLfloat objeto_ambient[] = { 0.33125f, 0.33125f, 0.33125f, 1.0f };
    GLfloat objeto_difusa[] = {0.3775f, 0.3775f, 0.3775f, 1.0f };
    GLfloat objeto_especular[] = {0.873911f, 0.873911f, 0.873911f, 1.0f };
    GLfloat objeto_brilho[] = {95.0f};

   glMaterialfv(GL_FRONT, GL_AMBIENT, objeto_ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, objeto_difusa);
   glMaterialfv(GL_FRONT, GL_SPECULAR, objeto_especular);
   glMaterialfv(GL_FRONT, GL_SHININESS, objeto_brilho);


}


void explosao::setMaterial_explosao(void)
{
    //silver
    GLfloat objeto_ambient[] = { 0.3745f, 0.11175f, 0.11175f, 1.0f };
    GLfloat objeto_difusa[] = {0.81424f, 0.14136f, 0.14136f, 1.0f };
    GLfloat objeto_especular[] = {0.927811f, 0.826959f, 0.826959f, 1.0f };
    GLfloat objeto_brilho[] = {90.8f};

   glMaterialfv(GL_FRONT, GL_AMBIENT, objeto_ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, objeto_difusa);
   glMaterialfv(GL_FRONT, GL_SPECULAR, objeto_especular);
   glMaterialfv(GL_FRONT, GL_SHININESS, objeto_brilho);


}
