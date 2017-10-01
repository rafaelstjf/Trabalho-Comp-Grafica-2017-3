#include <iostream>
#include <GL/glut.h>
#include "Modelo.h"
#include <stdlib.h>
#include <sstream>
#include <string>
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
//Funcoes
void init(void);
void display(void);
void idle(void);
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
void motion(int x, int y);
void mouse(int button, int state, int x, int y);
void desenhaVertices(Modelo *m);
void desenhaFaces(Modelo *m);
//Variaveis
float rotationX = 0.0, rotationY = 0.0;
int last_x, last_y;
bool light = true;
bool zbuffer = true;
bool backface = true;
int width = 500, height = 500;
int distOrigem = 30;
int modeloAtual = 1;
bool wireframe = true;
bool trocaModelo = true;
int qntTriangulos;
string bufferTitulo;
//modelos
Modelo *ant = new Modelo("ant.ply");
Modelo *apple = new Modelo("apple.ply");
Modelo *cow = new Modelo("cow.ply");
Modelo *inputUsuario;

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL); // Utiliza cor do objeto como material
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST); // Habilita Z-buffer
    glEnable(GL_CULL_FACE);  // Habilita Backface-Culling
}
void display(void)
{
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)width / (GLfloat)height, 1.0, 200.0);
    bufferTitulo = to_string(qntTriangulos);
    glutSetWindowTitle(bufferTitulo.c_str());    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 10.0, distOrigem, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    switch (modeloAtual)
    {
    case 1:
        desenhaFaces(ant);
        break;
    case 2:
        desenhaFaces(apple);
        break;
    case 3:
        desenhaFaces(cow);
        break;
    case 4:

        break;
    case 5:

        break;
    case 6:

        break;
    }
    glutSwapBuffers();
}
void idle(void)
{
    glutPostRedisplay();
}
void reshape(int w, int h)
{
    width = w;
    height = h;
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}
void desenhaVertices(Modelo *m)
{
    glColor3f(1.0, 0.0, 0.0);
    double **vertices = m->getVertices();
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < m->getTamVertices(); i++)
    {
        glVertex3f(vertices[i][0], vertices[i][1], vertices[i][2]);
    }
    glEnd();
}
void desenhaFaces(Modelo *m)
{
   
    glColor3f(0.0, 1.0, 0.0);
    double **vertices = m->getVertices();
    int **faces = m->getFaces();
    if(trocaModelo){
        qntTriangulos = m->getTamFaces()*2;
        trocaModelo = false;
    }
    if (wireframe)
        glBegin(GL_LINE_LOOP);
    else
        glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < m->getTamFaces(); i++)
    {
        for (int k = 0; k < 4; k++)
            glVertex3f(vertices[faces[i][k]][0], vertices[faces[i][k]][1], vertices[faces[i][k]][2]);
    }
    glEnd();
}
void keyboard(unsigned char key, int x, int y)
{
    string nomeModelo;
    switch (tolower(key))
    {
    case 'l':
        modeloAtual = 1;
        trocaModelo = true;
        break;
    case '2':
        modeloAtual = 2;
        trocaModelo = true;
        break;
    case '3':
        modeloAtual = 3;
        trocaModelo = true;
        break;
    case '4':
        modeloAtual = 4;
        trocaModelo = true;
        break;
    case '5':
        modeloAtual = 5;
        trocaModelo = true;
        break;
    case '6':
        cout << "Carregando modelo do arquivo" << endl;
        cout << "Digite o nome+extensao do modelo" << endl;
        cin >> nomeModelo;
        inputUsuario = new Modelo(nomeModelo);
        modeloAtual = 6;
        trocaModelo = true;
        break;
    case 'f': //muda o wireframe
        wireframe = !wireframe;
        break;
    }
}
void motion(int x, int y)
{
    rotationX += (float)(y - last_y);
    rotationY += (float)(x - last_x);
    last_x = x;
    last_y = y;
}
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        last_x = x;
        last_y = y;
    }
    if (button == 3 && state == GLUT_DOWN)
    { //zoom out
        distOrigem--;
    }
    if (button == 4 && state == GLUT_DOWN)
    { //zoom in
        distOrigem++;
    }
}