#include <iostream>
#include <GL/glut.h>
#include "Modelo.h"
using namespace std;

//Funcoes
void init(void);
void display(void);
void idle(void);
void reshape(int w, int h);
void keyboard (unsigned char key, int x, int y);
void motion(int x, int y );
void mouse(int button, int state, int x, int y);
void desenhaVertices(Modelo* m);
//Variaveis
float rotationX = 0.0, rotationY = 0.0;
int   last_x, last_y;
bool light     = true;
bool zbuffer   = true;
bool backface  = true;
int width = 500, height = 500;
int distOrigem = 30;
int modeloAtual = 1;
//modelos
Modelo* formiga = new Modelo("ant.ply");
Modelo* apple = new Modelo("apple.ply");
Modelo* inputUsuario;

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (width, height);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc( mouse );
    glutMotionFunc( motion );
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);           // Utiliza cor do objeto como material
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);               // Habilita Z-buffer
    glEnable(GL_CULL_FACE);                // Habilita Backface-Culling
}
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(60.0, (GLfloat) width/(GLfloat) height, 1.0, 200.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity ();
    gluLookAt (0.0, 0.0, distOrigem, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    switch (modeloAtual) {
    case 1:
        desenhaVertices(formiga);
        break;
    case 2:

        break;

    case 3:

        break;
    case 4:

        break;
    case 5:

        break;
    case 6:

        break;
    }
}
void idle(void)
{
    glutPostRedisplay();
}
void reshape (int w, int h)
{
    width = w;
    height = h;
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
}
void desenhaVertices(Modelo* m)
{
    double** vertices = m->getVertices();
    for(int i =0; i< m->getTamVertices(); i++ )
    {
        glVertex3f(vertices[i][0], vertices[i][1], vertices[i][2]);
    }
}
void keyboard (unsigned char key, int x, int y)
{
    string nomeModelo;
    switch (tolower(key))
    {
    case 'l':
        modeloAtual = 1;
        break;
    case '2':
        modeloAtual = 2;
        break;
    case '3':
        modeloAtual = 3;
        break;
    case '4':
        modeloAtual = 4;
        break;
    case '5':
        modeloAtual = 5;
        break;
    case '6':
        cout << "Carregando modelo do arquivo" << endl;
        cout << "Digite o nome+extensao do modelo" << endl;
        cin >> nomeModelo;
        inputUsuario = new Modelo(nomeModelo);
        modeloAtual = 6;
        break;
    }
}
void motion(int x, int y )
{
    rotationX += (float) (y - last_y);
    rotationY += (float) (x - last_x);

    last_x = x;
    last_y = y;
}
void mouse(int button, int state, int x, int y)
{
    if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
    {
        last_x = x;
        last_y = y;
    }
}
