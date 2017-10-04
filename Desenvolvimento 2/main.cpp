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
void exibirEixos();
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
bool back_face = false;
bool flat = false;
int qntTriangulos;
string bufferTitulo;
//modelos
Modelo *ant = new Modelo("ant.ply");
Modelo *apple = new Modelo("teapot.ply");
Modelo *cow = new Modelo("cow.ply");
Modelo *ketchup = new Modelo("ketchup.ply");
Modelo *turbine = new Modelo("turbine.ply");
Modelo *inputUsuario = nullptr;

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
    glClearColor(0.4, 0.4, 0.4, 0.0);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_COLOR_MATERIAL); // Utiliza cor do objeto como material

    // Cor da fonte de luz (RGBA)
    GLfloat cor_luz[] = {0.6, 0.6, 0.6, 1.0};
    // Posicao da fonte de luz. Ultimo parametro define se a luz sera direcional (0.0) ou tera uma posicional (1.0)
    GLfloat posicao_luz[] = {120.0, 100.0, -50.0, 1.0};
    GLfloat posicao_luz2[] = {-120.0, -100.0, 50.0, 1.0};
    // Define parametros da luz
    glLightfv(GL_LIGHT0, GL_AMBIENT, cor_luz);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, cor_luz);
    glLightfv(GL_LIGHT0, GL_SPECULAR, cor_luz);
    glLightfv(GL_LIGHT0, GL_POSITION, posicao_luz);
    glLightfv(GL_LIGHT1, GL_AMBIENT, cor_luz);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, cor_luz);
    glLightfv(GL_LIGHT1, GL_SPECULAR, cor_luz);
    glLightfv(GL_LIGHT1, GL_POSITION, posicao_luz2);

    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_DEPTH_TEST); // Habilita Z-buffer
    glEnable(GL_CULL_FACE);  // Habilita Backface-Culling
    glEnable(GL_NORMALIZE);
}
void exibirEixos()
{
    /*   glBegin(GL_LINES);
    glVertex3f();
    glVertex3f();
    glEnd();
    glBegin(GL_LINES);
    glVertex3f();
    glVertex3f();
    glEnd();
    glBegin(GL_LINES);
    glVertex3f();
    glVertex3f();
    glEnd();*/
}
void setMaterial(void)
{
    //silver
    GLfloat objeto_ambient[] = {0.19225, 0.19225, 0.19225, 1.0};
    GLfloat objeto_difusa[] = {0.50754, 0.50754, 0.50754, 1.0};
    GLfloat objeto_especular[] = {0.508273, 0.508273, 0.508273, 1.0};
    GLfloat objeto_brilho[] = {0.4};


    // Define os parametros da superficie a ser iluminada
    glMaterialfv(GL_FRONT, GL_AMBIENT, objeto_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, objeto_difusa);
    glMaterialfv(GL_FRONT, GL_SPECULAR, objeto_especular);
    glMaterialfv(GL_FRONT, GL_SHININESS, objeto_brilho);
}

void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)width / (GLfloat)height, 0.01, 20000000.0);
    bufferTitulo = patch::to_string(qntTriangulos);
    glutSetWindowTitle(bufferTitulo.c_str());
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, distOrigem, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glRotatef(rotationY, 0.0, 1.0, 0.0);
    glRotatef(rotationX, 1.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);

    if (zbuffer)
        glEnable(GL_DEPTH_TEST); // Habilita Z-buffer
    else
        glDisable(GL_DEPTH_TEST); // Habilita Z-buffer

    if (back_face)
        glEnable(GL_CULL_FACE); // Habilita Backface-Culling
    else
        glDisable(GL_CULL_FACE); // Habilita Backface-Culling
    if (flat)
        glShadeModel(GL_FLAT);
    else
        glShadeModel(GL_SMOOTH);

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
        desenhaFaces(turbine);
        break;
    case 5:
        desenhaFaces(ketchup);
        break;
    case 6:
        if (inputUsuario != nullptr)
            desenhaFaces(inputUsuario);
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

    for (int i = 0; i < m->getTamVertices(); i++)
    {
        glBegin(GL_LINE_LOOP);
        glVertex3f(vertices[i][0], vertices[i][1], vertices[i][2]);
        glEnd();
    }
}
void desenhaFaces(Modelo *m)
{

    glColor3f(1.0, 1.0, 1.0);
    double **vertices = m->getVertices();
    int **faces = m->getFaces();
    double **normal = m->getNormal();
    if (trocaModelo)
    {
        qntTriangulos = m->getTamFaces();
        trocaModelo = false;
    }
    for (int i = 0; i < m->getTamFaces(); i++)
    {
        glFrontFace(GL_CCW);
        setMaterial();
        if (wireframe)
            glBegin(GL_LINE_LOOP);
        else
            glBegin(GL_POLYGON);
        glNormal3f(normal[i][0], normal[i][1], normal[i][2]);
        for (int k = 1; k < 4; k++)
            glVertex3f(vertices[faces[i][k]][0], vertices[faces[i][k]][1], vertices[faces[i][k]][2]);
        glEnd();
    }
}
void keyboard(unsigned char key, int x, int y)
{
    string nomeModelo;
    switch (tolower(key))
    {
    case '1':
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
        modeloAtual = 6;
        trocaModelo = 6;
        break;
    case 'c':
        cout << "Carregando modelo do arquivo" << endl;
        cout << "Digite o nome+extensao do modelo" << endl;
        cin >> nomeModelo;
        inputUsuario = new Modelo(nomeModelo);
        break;
    case 'f': //muda o wireframe
        wireframe = !wireframe;
        break;
    case '+':
        distOrigem--;
        if (distOrigem < 0)
            distOrigem = 0;
        break;
    case '-':
        distOrigem++;
        if (distOrigem > 180)
            distOrigem = 180;
        break;
    case 'b':
        back_face = !back_face;
        if (back_face)
            cout << "Back face culling ativado!" << endl;
        else
            cout << "Back face culling desativado!" << endl;
        break;
    case 'z':
        zbuffer = !zbuffer;
        if (zbuffer)
            cout << "Zbuffer culling ativado!" << endl;
        else
            cout << "Zbuffer culling desativado!" << endl;
        break;
     case 't':
        flat = !flat;
        if (flat)
            cout << "Flat ativado!" << endl;
        else
            cout << "Smooth ativado!" << endl;
        break;
    case 27:
        exit(0);
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
    {
        //zoom out
        distOrigem--;
    }
    if (button == 4 && state == GLUT_DOWN)
    {
        //zoom in
        distOrigem++;
    }
}
