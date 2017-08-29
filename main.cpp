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
#define NUM 10
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
int height = 480;
float jogadorx = 0, jogadory = 0, mousex, mousey; //posicao do jogador e do mouse
int pontos = 0;                                   //variavel para contar os pontos
int vidas = 10;                                   //variavel para controle de vidas
int dificuldade = 1;                              //variavel para controle de dificuldade
bool mouseDown = false;
//funcoes
void idle();
void display();
void init();
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void desenhaPlano();
void init_esfera(int i);
void motion(int x, int y);
void output(char *string);

typedef struct esfera
{
    float x, y;
    double raio;
    float velocidade;
    void draw_esfera()
    { //funcao para desenhas as esferas
        glPushMatrix();
        glColor3f((velocidade - 10) / 10, 0.0, 1 - ((velocidade - 10) / 10)); //cor muda com a velocidade
        glTranslatef(x, y, 0.0);
        glutSolidSphere(raio, 100, 100);
        glPopMatrix();
    }
} esfera;
esfera ball[NUM]; // esferas "inimigas"

int main(int argc, char **argv)
{
    srand(time(NULL)); // dando aleatoriedade ao funcao rand() com o tempo do pc
    for (int i = 0; i < NUM; i++)
    {
        init_esfera(i); // iniciando esferas
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Desenvolvimento 1");
    glutMouseFunc(mouse);

    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    init();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}

void output(const char *string) //funcao para printar na tela
{
    glColor3f(0, 0, 0);     //cor do texto
    glRasterPos2f(-99, 95); //local
    int len, i;
    len = (int)strlen(string);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string[i]); //printa com a fonte GLUT_BITMAP_8_BY_13
    }
}

void init_esfera(int i)
{                                                      //Inicia as esferas ou reinicia depois de colidir
    std::mt19937 rng(rand());                          // seed do gerador vinda do tempo
    std::uniform_int_distribution<int> uni(-100, 100); // posicao maxima e minima das esferas
    auto random_x = uni(rng);                          //gerando valor aleatorio
    ball[i].x = random_x;
    ball[i].y = 100;
    std::uniform_int_distribution<int> duni(5, 15); //raio maximo e minimo
    auto random_raio = duni(rng);                   //gerando valor aleatorio
    ball[i].raio = random_raio;
    std::uniform_int_distribution<int> tuni(10, 20); //velocidade maxima e minima
    auto random_velo = tuni(rng);                    //gerando valor aleatorio
    ball[i].velocidade = random_velo;
}

void desenhaPlano()
{
    glColor3f(1.0, 0.0, 0.0); //vermelho para teste
    glBegin(GL_QUADS);
    glVertex2f(-100.0, -90.0);
    glVertex2f(100.0, -90.0);
    glVertex2f(100.0, -100.0);
    glVertex2f(-100.0, -100.0);
    glEnd();
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    desenhaPlano();
    for (int i = 0; i < dificuldade; i++)
    {
        ball[i].draw_esfera();
    }
    string print = "Pontos: " + patch::to_string(pontos) + "     Vidas: " + patch::to_string(vidas); //texto de pontuacao
    if (vidas == 0)
    {
        print = "Parabens voce fez: " + patch::to_string(pontos) + "  Aperte r para tentar novamente!"; //texto de fim de jogo
    }
    output(print.c_str()); //converte para char* e envia para a funcao
    glColor3f(0.0, 1.0, 0.0);
    glTranslatef(jogadorx, jogadory, 0.0);
    glutSolidSphere(10, 100, 100); // Jogador
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
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    case 'r': //resetando o game
        dificuldade = 1;
        pontos = 0;
        vidas = 10;
        for (int i = 0; i < NUM; i++)
        {
            init_esfera(i); // iniciando esferas
        }
        break;
    }
}
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN) //botao esquerdo do mouse pressionado
        {                       // Conversao de escala dos eixos do mouse para valores do ortho
            x = (float)(x * 0.3125 - 100);
            y = (float)(-1 * y * 0.417 + 100);

            //so seleciona o jogador clicando dentro do seu raio
            if (sqrt((x - jogadorx) * (x - jogadorx) + (y - jogadory) * (y - jogadory)) < (10))
                mouseDown = true;
        }
        else //botao esquerdo do mouse solto
        {
            mouseDown = false;
        }
    }
}
void motion(int x, int y) //funcao que pega os valores do mouse em tempo real
{

    if (mouseDown)
    {
        //se o mouse estiver pressionado atualizar os valores da esfera do jogador
        // Conversao de escala dos eixos do mouse para valores do ortho
        jogadorx = (float)(x * 0.3125 - 100);
        jogadory = (float)(-1 * y * 0.417 + 100);
        if (jogadorx > 100)
            jogadorx = 100; //limitando a movimentacao com as bordas da tela
        if (jogadorx < -100)
            jogadorx = -100;
        if (jogadory > 100)
            jogadory = 100;
        if (jogadory < -100)
            jogadory = -100;
    }
}

void idle()
{
    glutPostRedisplay();

    float t, dt;
    static float tLast = 0.0;
    /* Get elapsed time and convert to s */
    t = glutGet(GLUT_ELAPSED_TIME);
    t /= 100.0;
    /* Calculate delta t */
    dt = t - tLast;
    //funcoes do professor para variacao de tempo a cima
    for (int i = 0; i < dificuldade; i++)
    {
        ball[i].y -= dt * ball[i].velocidade; // queda simple para teste
        if ((ball[i].y - ball[i].raio) < -90) //Colisao simples com o plano;
        {
            init_esfera(i);
            vidas--;
        }
        if (sqrt((ball[i].x - jogadorx) * (ball[i].x - jogadorx) + (ball[i].y - jogadory) * (ball[i].y - jogadory)) < (10 + ball[i].raio)) //colisao jogador esfera
        {
            init_esfera(i);
            pontos += ball[i].raio;
        }
    }
    tLast = t;
    if (pontos > dificuldade * 100) // a cada 100 pontos +1 de dificuldade
    {
        dificuldade++; //quantidade de bolinhas na tela e igual a dificuldade agora
    }
    if (vidas <= 0) //terminando o jogo
        dificuldade = 0;
}
/************
formula da colisao veio daqui:
https://www.opengl.org/discussion_boards/showthread.php/159530-Circle-Circle-Collision
************/
