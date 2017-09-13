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
#include "menu.h"
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
int width = 800;
int height = 450;
float jogadorx = 0, jogadory = 0, mousex, mousey; //posicao do jogador e do mouse
int pontos = 0;                                   //variavel para contar os pontos
int vidas = 10;                                   //variavel para controle de vidas
int dificuldade = 1;                              //variavel para controle de dificuldade
bool mouseDown = false;
bool fullscreen = false;
bool inteira[10];
float clok = 1;
//funcoes
void idle();
void display();
void init();
void mouse(int button, int state, int x, int y);
void drawAim();
void motion(int x, int y);
void reshape(int w, int h);
void keyboardPress(unsigned char key, int x, int y);
void specialKeysPress(int key, int x, int y);
void startWindow(int argc, char **argv);
menu inicio;
bool comecou = false;
bool opcao = 0;
int fase = 1,f=0;
filaAnima explosoes = filaAnima(10);
filaAnima inimigos = filaAnima(10);

int main(int argc, char **argv)
{
    for(int i = 0; i<10 ; i++)
        inteira[i]=true;
    srand(time(NULL));
    startWindow(argc, argv);
    glutMainLoop();
    return 0;
}

void startWindow(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Trabalho 1");
    glutMouseFunc(mouse);
    //glutReshapeFunc(reshape);
    glutPassiveMotionFunc(motion);
    glutKeyboardFunc(keyboardPress);
    glutSpecialFunc( specialKeysPress );
    init();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
}

void drawAim()
{
    glColor3f(0.0, 0.0, 1.0);
    //quadrado
    glBegin(GL_LINE_LOOP);
    glVertex2f(jogadorx - 4, jogadory - 2.25);
    glVertex2f(jogadorx + 4, jogadory - 2.25);
    glVertex2f(jogadorx + 4, jogadory + 2.25);
    glVertex2f(jogadorx - 4, jogadory + 2.25);
    glEnd();
    //Crosshair
    glBegin(GL_LINES);
    glVertex2f(jogadorx - 4, jogadory);
    glVertex2f(jogadorx + 4, jogadory);
    glVertex2f(jogadorx, jogadory - 2.25);
    glVertex2f(jogadorx, jogadory + 2.25);
    glEnd();
}

void display()
{
    int cor = fase%2;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    if(!comecou){
    inicio.draw((int)opcao);
    }else{
    explosoes.desenhos();
    inimigos.desenhos();
    //teste->draw(jogadorx, -jogadory,1.0,0.0,0.0);
    /******   CANHOES  *******/
    glColor3f(0, cor, 1);
    glBegin(GL_QUADS);
    glVertex2f(110, -88.75);
    glVertex2f(90, -88.75);
    glVertex2f(90, -77.5);
    glVertex2f(110, -77.5);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(-70, -88.75);
    glVertex2f(-90, -88.75);
    glVertex2f(-90, -77.5);
    glVertex2f(-70, -77.5);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(290, -88.75);
    glVertex2f(270, -88.75);
    glVertex2f(270, -77.5);
    glVertex2f(290, -77.5);
    glEnd();
    /***** FIM CANHOES *****/
    /*****   CIDADES   *****/
    glColor3f(cor, 1, 0);
    int i=3;
    for (int cd = -60; cd <= 240; cd += 50)
    {
        if (cd != 90)
        {
            if(inteira[i]){
                glBegin(GL_QUADS);
                glVertex2f(cd + 20, -94.375);
                glVertex2f(cd, -94.375);
                glVertex2f(cd, -88.75);
                glVertex2f(cd + 20, -88.75);
                glEnd();
            }
            i++;
        }
    }
    /***** FIM CIDADES *****/
    /*****    BALAS    *****/
    glColor3f(0, cor, 1);
    if(!inteira[2])explosoes.bala[2]=0;
    for (int bl = 0; bl < explosoes.bala[2]; bl++)
    {
        glBegin(GL_QUADS);
        glVertex2f(86 + 3 * bl, -96.625);
        glVertex2f(84 + 3 * bl, -96.625);
        glVertex2f(84 + 3 * bl, -92.125);
        glVertex2f(86 + 3 * bl, -92.125);
        glEnd();
    }
    if(!inteira[0])explosoes.bala[0]=0;
    for (int bl = 0; bl < explosoes.bala[0]; bl++)
    {
        glBegin(GL_QUADS);
        glVertex2f(-94 + 3 * bl, -96.625);
        glVertex2f(-96 + 3 * bl, -96.625);
        glVertex2f(-96 + 3 * bl, -92.125);
        glVertex2f(-94 + 3 * bl, -92.125);
        glEnd();
    }
    if(!inteira[1])explosoes.bala[1]=0;
    for (int bl = 0; bl < explosoes.bala[1]; bl++)
    {
        glBegin(GL_QUADS);
        glVertex2f(264 + 3 * bl, -96.625);
        glVertex2f(262 + 3 * bl, -96.625);
        glVertex2f(262 + 3 * bl, -92.125);
        glVertex2f(264 + 3 * bl, -92.125);
        glEnd();
    }
    inicio.drawf(fase,pontos);
    drawAim();
    }
    glutSwapBuffers();
}

void keyboardPress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    case 13:
        if(!comecou&&!opcao)
            comecou=true;
        break;
    case 'f':
        if (fullscreen)
        {
            glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR);
            glutReshapeWindow(800, 450);
            glutPositionWindow(50, 50);
        }
        else
        {
            glutSetCursor(GLUT_CURSOR_NONE);
            glutFullScreen();
        }
        fullscreen = !fullscreen;
        break;
    }
}

void init()
{
    glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR);
    glClearColor(0.7, 0.7, 0.7, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100.0, 300, -100.0, 125, -100.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void mouse(int button, int state, int x, int y)
{
    if(comecou){
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            mouseDown = true;
            float xreal = (float)(mousex / 2 - 100);
            float yreal = (float)(-1 * mousey / 2 + 125);
            if (xreal < 20 && explosoes.bala[0] > 0)
            {
                explosoes.addObjeto(xreal, yreal, -80, -83.125);
                explosoes.bala[0]--;
            }
            else if (xreal > 180 && explosoes.bala[1] > 0)
            {
                explosoes.addObjeto(xreal, yreal, 280, -83.125);
                explosoes.bala[1]--;
            }
            else if (explosoes.bala[2] > 0)
            {
                explosoes.addObjeto(xreal, yreal, 100, -83.125);
                explosoes.bala[2]--;
            }
            else if (xreal < 100 && explosoes.bala[0] > 0)
            {
                explosoes.addObjeto(xreal, yreal, -80, -83.125);
                explosoes.bala[0]--;
            }
            else if (explosoes.bala[1] > 0)
            {
                explosoes.addObjeto(xreal, yreal, 280, -83.125);
                explosoes.bala[1]--;
            }
            else if (explosoes.bala[0] > 0)
            {
                explosoes.addObjeto(xreal, yreal, -80, -83.125);
                explosoes.bala[0]--;
            }
        }
    }
    }
}
void motion(int x, int y) //funcao que pega os valores do mouse em tempo real
{
    mousex = x;
    mousey = y;
}

void specialKeysPress(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:
		    opcao=!opcao;
            break;
		case GLUT_KEY_DOWN:
		    opcao=!opcao;
            break;
		case GLUT_KEY_RIGHT:
            break;
        case GLUT_KEY_LEFT:
            break;
	}
	glutPostRedisplay();
}
void idle()
{
    for(int i = 0; i<9 ; i++){
        inteira[10]=false;
        if(inteira[i])
            inteira[10]=true;
    }
    glutPostRedisplay();
    float t, dt;
    static float tLast = 0.0;
    /* Get elapsed time and convert to s */
    t = glutGet(GLUT_ELAPSED_TIME);
    t /= 500.0;
    /* Calculate delta t */
    dt = t - tLast;
    explosoes.atualizaTempo(dt);
    inimigos.atualizaTempo(dt);
    //funcoes do professor para variacao de tempo a cima
    if(!comecou){

    }else{
    jogadorx = (float)(mousex / 2 - 100);
    jogadory = (float)(-1 * mousey / 2 + 125);
    /***** MISSEIS *****/
    if(inteira[10]&&f<fase)
    if (clok > 2)
    {
        f++;
        for (int i = 0; i < 3; i++)
        {
            std::mt19937 rng(rand());
            std::uniform_int_distribution<int> uni(-100, 300);
            auto random_x = uni(rng);
            std::uniform_int_distribution<int> duni(0, 8);
            auto cit = duni(rng);
            if(inteira[cit]){
            if (cit == 2)
            {
                inimigos.addObjeto(100, -77.5, random_x, 125, 30000-(fase*2000),cit);
            }
            else if (cit == 0)
            {

                inimigos.addObjeto(-80, -77.5, random_x, 125, 30000-(fase*2000),cit);
            }
            else if (cit == 1)
            {
                inimigos.addObjeto(280, -77.5, random_x, 125, 30000-(fase*2000),cit);
            }
            else if (cit == 3)
            {
                inimigos.addObjeto(-50, -88.75, random_x, 125, 30000-(fase*2000),cit);
            }
            else if (cit == 4)
            {
                inimigos.addObjeto(0, -88.75, random_x, 125, 30000-(fase*2000),cit);
            }
            else if (cit == 5)
            {
                inimigos.addObjeto(50, -88.75, random_x, 125, 30000-(fase*2000),cit);
            }
            else if (cit == 6)
            {
                inimigos.addObjeto(150, -88.75, random_x, 125, 30000-(fase*2000),cit);
            }
            else if (cit == 7)
            {
                inimigos.addObjeto(200, -88.75, random_x, 125, 30000-(fase*2000),cit);
            }
            else if (cit == 8)
            {
                inimigos.addObjeto(250, -88.75, random_x, 125, 30000-(fase*2000),cit);
            }
            }else i--;
        }
        clok = 0;
    }
    pontos+=inimigos.colisao(explosoes);
    pontos+=inimigos.colisao(inimigos);
    if(inteira[10])
    inimigos.dividir(inteira);
    clok += dt;
    //std::cout<<inimigos.explo.size()<<std::endl;
    for(unsigned int i = 0;i<inimigos.explo.size();i++){
        if(inimigos.explo[i].destruiu)
        if(inimigos.explo[i].alvo<9){
            inteira[inimigos.explo[i].alvo]=false;
        }
    }
    if(fase==f&&inimigos.explo.size()==0){
        fase++;
        f=0;
        pontos+=explosoes.bala[0]*10;
        explosoes.bala[0]=10;
        inteira[0]=true;
        pontos+=explosoes.bala[1]*10;
        explosoes.bala[1]=10;
        inteira[1]=true;
        pontos+=explosoes.bala[2]*10;
        explosoes.bala[2]=10;
        inteira[2]=true;
        clok=1;
         for(int i = 0; i<9 ; i++){
            if(inteira[i])
                pontos+=100;
         }
    }
    }
    tLast = t; //atualiza o tempo, deixar no fim da idle
}
