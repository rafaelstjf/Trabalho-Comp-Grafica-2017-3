#include <iostream>
#include <GL/glut.h>

using namespace std;

//Funcoes
void init(void);
void display(void);
void idle(void);
void reshape(int w, int h);
void keyboard (unsigned char key, int x, int y);
void motion(int x, int y );
void mouse(int button, int state, int x, int y);

//Variaveis
float rotationX = 0.0, rotationY = 0.0;
int   last_x, last_y;
bool light     = true;
bool zbuffer   = true;
bool backface  = true;
int width = 500, height = 500;
int distOrigem = 30;

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
void init(void){
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);           // Utiliza cor do objeto como material
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);               // Habilita Z-buffer
    glEnable(GL_CULL_FACE);                // Habilita Backface-Culling
}
void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(60.0, (GLfloat) width/(GLfloat) height, 1.0, 200.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity ();
    gluLookAt (0.0, 0.0, distOrigem, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
void idle(void){
    glutPostRedisplay();
}
void reshape (int w, int h)
{
   width = w;
   height = h;
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
}
void keyboard (unsigned char key, int x, int y)
{
   switch (tolower(key))
   {
      case 'l'	:
      cout << "Xablau" << endl;
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
