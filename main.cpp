#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
//Variaveis globais
int width = 640;
int height = 480;
//funcoes
void idle();
void display();
void init();
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void desenhaPlano();

typedef struct esfera {
int x,y;
double raio;
} esfera;

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (width, height);
    glutInitWindowPosition (100, 100);
    glutCreateWindow("Desenvolvimento 1");
    glutMouseFunc(mouse);  
    glutKeyboardFunc(keyboard);    
    init();
    glutDisplayFunc(display);        
    //glutIdleFunc(idle);
    glutMainLoop();
    return 0;    
}

void desenhaPlano(){
    glColor3f(1.0, 0.0, 0.0); //vermelho para teste
    glBegin(GL_LINES);
        glVertex2f(-100.0, 100.0);
        glVertex2f(100.0, 100.0);
        
    glEnd();
}
void display(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    desenhaPlano();
    glutSwapBuffers();
}
void init(){
    glClearColor(0.7, 0.7, 0.7, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();    
    glOrtho(-100.0, 100.0, -100.0, 100.0, -1.0, 1.0);    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void keyboard(unsigned char key, int x, int y){

}
void mouse(int button, int state, int x, int y){
    
}
void idle(){

}