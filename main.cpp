#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
//Variaveis globais
int width = 640;
int height = 480;
//funcoes
void idle();
void display();
void ini();


int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (width, height);
    glutInitWindowPosition (100, 100);
    glutCreateWindow("Desenvolvimento 1");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;    
}
