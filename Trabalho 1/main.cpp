#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <time.h>
#include <random> // Vai em build options e marca onde ta escrito Have g++ follow the C++11 ISO C++ language standard [-std=c++11]
#include <math.h>
#include <string>
#include <sstream>
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
void desenhaCruz();
void motion(int x, int y);

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Desenvolvimento 1");
    glutMouseFunc(mouse);

    glutPassiveMotionFunc(motion);
    init();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}

void desenhaCruz()
{
    glColor3f(0.0, 0.0, 1.0); //vermelho para teste
    glBegin(GL_LINE_LOOP);
    glVertex2f(jogadorx - 3,  jogadory - 3);
    glVertex2f(jogadorx + 3, jogadory - 3);
    glVertex2f(jogadorx+3, jogadory + 3);    
    glVertex2f(jogadorx-3, jogadory + 3);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(jogadorx - 3, jogadory);
    glVertex2f(jogadorx + 3, jogadory);
    glVertex2f(jogadorx, jogadory - 3);
    glVertex2f(jogadorx, jogadory + 3);
    glEnd();
}
void display()
{
    // glutFullScreen();
    glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    desenhaCruz();
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
    t /= 150.0;
    /* Calculate delta t */
    dt = t - tLast;
    //funcoes do professor para variacao de tempo a cima
}