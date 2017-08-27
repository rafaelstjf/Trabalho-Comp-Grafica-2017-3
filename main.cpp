#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <time.h>
#include <random> // Vai em build options e marca onde ta escrito Have g++ follow the C++11 ISO C++ language standard [-std=c++11]
#define NUM 10
//Variaveis globais
int width = 640;
int height = 480;
float jogadorx = 0, jogadory = 0; //posicao do jogador
//funcoes
void idle();
void display();
void init();
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void desenhaPlano();
void init_esfera(int i);

typedef struct esfera {
int x,y;
double raio;
void draw_esfera(){ //funcao para desenhas as esferas
    glPushMatrix();
    glColor3f (0.0, 0.0, 1.0);
    glTranslatef(x,y, 0.0);

    glutSolidSphere(raio, 100, 100);
    glPopMatrix();
}
} esfera;
esfera ball[NUM]; // esferas "inimigas"


int main(int argc, char** argv){
    srand(time(NULL)); // dando aleatoriedade ao funcao rand() com o tempo do pc
    for(int i=0; i<NUM; i++)
    {
        init_esfera(i); // iniciando esferas
    }
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (width, height);
    glutInitWindowPosition (100, 100);
    glutCreateWindow("Desenvolvimento 1");
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    init();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}

void init_esfera(int i){ //Inicia as esferas ou reinicia depois de colidir
    std::mt19937 rng(rand()); // seed do gerador vinda do tempo
    std::uniform_int_distribution<int> uni(-100,100); // posicao maxima e minima das esferas
    auto random_x = uni(rng); //gerando valor aleatorio
    ball[i].x =random_x;
    ball[i].y=100;
    std::uniform_int_distribution<int> duni(5,15); //raio maximo e minimo
    auto random_raio = duni(rng); //gerando valor aleatorio
    ball[i].raio = random_raio;
}

void desenhaPlano(){
    glColor3f(1.0, 0.0, 0.0); //vermelho para teste
    glBegin(GL_LINES);
        glVertex2f(-100.0, -90.0);
        glVertex2f(100.0, -90.0);

    glEnd();
}
void display(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    desenhaPlano();
    for(int i=0; i<NUM; i++)
    {
        ball[i].draw_esfera();
    }
    glColor3f (1.0, 1.0, 0.0);
    glTranslatef(jogadorx,jogadory, 0.0);
    glutSolidSphere(10, 100, 100); // Jogador
    glutSwapBuffers();
}
void init(){
    glClearColor(0.7, 0.7, 0.7, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100.0, 100.0, -100.0, 100.0, -100.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void keyboard(unsigned char key, int x, int y){

}
void mouse(int button, int state, int x, int y){

}
void idle(){
    glutPostRedisplay();
    for(int i=0; i<NUM; i++)
    {
        ball[i].y--;  // queda simple para teste
        if((ball[i].y-ball[i].raio)<-90) //Colisao simples com o plano;
        {
            init_esfera(i);
        }
    }
}
