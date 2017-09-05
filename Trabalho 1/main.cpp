#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <time.h>
#include <random> // Vai em build options e marca onde ta escrito Have g++ follow the C++11 ISO C++ language standard [-std=c++11]
#include <math.h>
#include <string>
#include <sstream>
#include "missile.h"
#include "filaAnima.h"
#include "explosao.h"
#ifdef __linux__
#include <cstring>
#endif
using namespace std;
namespace patch //Correcao da funcao to_string
{
template <typename T>
std::string to_string(const T &n)
{
    std::ostringstream stm;
    stm << n;
    return stm.str();
}
}
//Variaveis globais
int width = 640;
int height = 640;
float jogadorx = 0, jogadory = 0, mousex, mousey; //posicao do jogador e do mouse
int pontos = 0;                                   //variavel para contar os pontos
int vidas = 10;                                   //variavel para controle de vidas
int dificuldade = 1;                              //variavel para controle de dificuldade
bool mouseDown = false;
//funcoes
void idle();
void display();
void init();
void mouse(int button, int state, int x, int y);
void drawAim();
void motion(int x, int y);
void reshape();
void startWindow(int argc, char **argv);
missile* teste = new missile();
filaAnima explosoes = filaAnima(10);

int main(int argc, char **argv)
{

    startWindow(argc, argv);
    return 0;
}

void startWindow(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Trabalho 1");
    glutMouseFunc(mouse);
    // glutReshapeFunc(reshape);
    glutPassiveMotionFunc(motion);
    init();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();
}

void drawAim(){
    glColor3f(0.0, 0.0, 1.0);
    //quadrado
    glBegin(GL_LINE_LOOP);
    glVertex2f(jogadorx - 3,  jogadory - 3);
    glVertex2f(jogadorx + 3, jogadory - 3);
    glVertex2f(jogadorx+3, jogadory + 3);
    glVertex2f(jogadorx-3, jogadory + 3);
    glEnd();
    /* Crosshair
    glBegin(GL_LINES);
    glVertex2f(jogadorx - 3, jogadory);
    glVertex2f(jogadorx + 3, jogadory);
    glVertex2f(jogadorx, jogadory - 3);
    glVertex2f(jogadorx, jogadory + 3);
    glEnd();
    */
}
void reshape(){

}
void display()
{
    // glutFullScreen();
    glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    drawAim();
    explosoes.desenhos();
    //teste->draw(jogadorx, -jogadory,1.0,0.0,0.0);
    /******   CANHOES  *******/
    glColor3f(0, 0, 1);
    glBegin(GL_QUADS);
    glVertex2f(5, -90);
    glVertex2f(-5, -90);
    glVertex2f(-5, -80);
    glVertex2f(5, -80);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(-85, -90);
    glVertex2f(-95, -90);
    glVertex2f(-95, -80);
    glVertex2f(-85, -80);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(95, -90);
    glVertex2f(85, -90);
    glVertex2f(85, -80);
    glVertex2f(95, -80);
    glEnd();
    /***** FIM CANHOES *****/
   /*****   CIDADES   *****/
    glColor3f(0, 1, 0);
    for (int cd = -80 ; cd<=70; cd+=25){
    if(cd!=-5){
    glBegin(GL_QUADS);
    glVertex2f(cd+10, -95);
    glVertex2f(cd, -95);
    glVertex2f(cd, -90);
    glVertex2f(cd+10, -90);
    glEnd();
    }}
    /***** FIM CIDADES *****/
   /*****    BALAS    *****/
    glColor3f(0, 0, 1);
    for (int bl = 0 ; bl<explosoes.bala[2]; bl++){
    glBegin(GL_QUADS);
    glVertex2f(-7+2*bl, -97);
    glVertex2f(-8+2*bl, -97);
    glVertex2f(-8+2*bl, -93);
    glVertex2f(-7+2*bl, -93);
    glEnd();
    }
    for (int bl = 0 ; bl<explosoes.bala[0]; bl++){
    glBegin(GL_QUADS);
    glVertex2f(-97+2*bl, -97);
    glVertex2f(-98+2*bl, -97);
    glVertex2f(-98+2*bl, -93);
    glVertex2f(-97+2*bl, -93);
    glEnd();
    }
    for (int bl = 0 ; bl<explosoes.bala[1]; bl++){
    glBegin(GL_QUADS);
    glVertex2f(82+2*bl, -97);
    glVertex2f(81+2*bl, -97);
    glVertex2f(81+2*bl, -93);
    glVertex2f(82+2*bl, -93);
    glEnd();
    }
    glutSwapBuffers();
}
void init()
{
    glClearColor(0.7, 0.7, 0.7, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100.0, 100.0, -100.0, 100.0, -100.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void mouse(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON){
        if(state == GLUT_DOWN){
            mouseDown = true;
            float xreal=(float)(x * 0.3125 - 100);
            float yreal=(float)(-1*y * 0.3125+100);
            if(xreal<-40&&explosoes.bala[0]>0){explosoes.addObjeto(xreal,yreal,-90,-85,0);}
            else if(xreal>40&&explosoes.bala[1]>0){explosoes.addObjeto(xreal,yreal,90,-85,1);}
            else if(explosoes.bala[2]>0){explosoes.addObjeto(xreal,yreal,0,-85,2);}
            else if(xreal<0&&explosoes.bala[0]>0){explosoes.addObjeto(xreal,yreal,-90,-85,0);}
            else if(explosoes.bala[1]>0){explosoes.addObjeto(xreal,yreal,90,-85,1);}
            else if(explosoes.bala[0]>0){explosoes.addObjeto(xreal,yreal,-90,-85,0);}

        }
    }

}
void motion(int x, int y) //funcao que pega os valores do mouse em tempo real
{
    mousex = x;
    mousey = y;
}

void idle()
{
    glutPostRedisplay();
    jogadorx = (float)(mousex * 0.3125 - 100);
    jogadory = (float)(-1 * mousey * 0.3125 + 100);
    float t, dt;
    static float tLast = 0.0;
    /* Get elapsed time and convert to s */
    t = glutGet(GLUT_ELAPSED_TIME);
    t /= 500.0;
    /* Calculate delta t */
    dt = t - tLast;
    explosoes.atualizaTempo(dt);
    //funcoes do professor para variacao de tempo a cima


    tLast = t;
}
