#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <time.h>
#include <random> // Vai em build options e marca onde ta escrito Have g++ follow the C++11 ISO C++ language standard [-std=c++11]
#include <math.h>
#include <string>
#include <sstream>
#include "filaAnima.h"
#include "Placar.h"
#include "explosao.h"
#include "menu.h"
#include "Modelo.h"
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
int indPlacar = 0;                                //variavel para controlar o indice do vetor do placar
bool mouseDown = false;
bool fullscreen = false;
bool inteira[11];//sabe se cada cidade ta inteira e na ultima posiçao se alguma ainda existe
float clok = 1;  //tempo entre os misseis
Placar *pl = new Placar();
bool comecou = false, emPlacar = false, confirmaInsercao = true;
bool opcao = 0; //posicao no menu
int fase = 1, f = 0; //fase e controle da mesma
bool pause = false; // pausa o game
filaAnima explosoes = filaAnima(10); //incializa a estrurura dos nossos tiros explosoes de duracao 10
filaAnima inimigos = filaAnima(10); //incializa a estrurura dos tiros inimigos explosoes de duracao 10
char nome[20];
Modelo *fundo = new Modelo("batata.ply");
Modelo *cidade= new Modelo("house3d.ply");
Modelo *cannon= new Modelo("cannon.ply");
float pos = 0;
float rotationX = 0.0, rotationY = 0.0;
//funcoes
void idle();
void display();
void init();
void mouse(int button, int state, int x, int y);
void drawAim(); //desenha mira
void motion(int x, int y);
void reshape(int w, int h);
void keyboardPress(unsigned char key, int x, int y);
void specialKeysPress(int key, int x, int y);
void startWindow(int argc, char **argv);//inicia o opengl
void drawScore();//desenha o score
menu inicio; //instancia um menu
void desenhaFaces(Modelo *m);

int main(int argc, char **argv)
{
    nome[0] = 'A';
    for (int i = 1; i < 20; i++)
    {
        nome[i] = ' ';
    }
    for (int i = 0; i < 11; i++)
        inteira[i] = true; //inicia as cidades inteiras
    srand(time(NULL)); //pega o tempo do sistema para randomizar a funcao rand
    startWindow(argc, argv);
    glutMainLoop();
    return 0;
}

void desenhaFaces(Modelo *m)
{

    glColor3f(1.0, 1.0, 1.0);
    double **vertices = m->getVertices();
    int **faces = m->getFaces();
    double **normal = m->getNormal();
    for (int i = 0; i < m->getTamFaces(); i++)
    {
        glFrontFace(GL_CCW);
        //setMaterial();
        glBegin(GL_POLYGON);
        glNormal3f(normal[i][0], normal[i][1], normal[i][2]);
        //cout << "normais: " << normal[i][0] << " " << normal[i][1] << " " << normal[i][2] << endl;
        for (int k = 1; k < 4; k++)
            glVertex3f(vertices[faces[i][k]][0], vertices[faces[i][k]][1], vertices[faces[i][k]][2]);
        glEnd();
    }
}




void drawScore() //funcao para printar o placar na tela
{
    glColor3f(0, 0, 0); //cor do texto

    int len;
    string output, titulo = "PLACAR";
    //borda Externa
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-60, -90);
    glVertex2f(260, -90);
    glVertex2f(260, 115);
    glVertex2f(-60, 115);
    glEnd();
    //Borda Interna
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-59, -89);
    glVertex2f(259, -89);
    glVertex2f(259, 114);
    glVertex2f(-59, 114);
    glEnd();
    //Texto
    glColor3f(0.0, 0.0, 0.0);
    glRasterPos2f(50, 80);
    for (int i = 0; i < 6; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, titulo[i]); //printa com a fonte GLUT_BITMAP_8_BY_13
    for (int k = 0; k < 10; k++)
    {

        glColor3f((k * 1.0) / 10, 0, 1 - ((k * 1.0) / 10));
        output = pl->getPosicao(k);
        len = (int)strlen(output.c_str());
        glRasterPos2f(45, 50 - 10 * k);
        for (int i = 0; i < len; i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, output[i]);
        }
    }
    if (!confirmaInsercao)
    {
        /*  //desenha triangulos
          glColor3f(0.0, 0.0, 1.0);
          glBegin(GL_TRIANGLES);
          glVertex2f(46+4.5*indPlacar, -53);
          glVertex2f(47 +4.5*indPlacar, -51);
          glVertex2f(48+4.5*indPlacar, -53);
          glEnd();
          glBegin(GL_TRIANGLES);
          glVertex2f(46+4.5*indPlacar, -63);
          glVertex2f(47 +4.5*indPlacar, -65);
          glVertex2f(48+4.5*indPlacar, -63);
          glEnd();
        */
        for (int i = 0; i < 20; i++)
        {
            //local
            if (i == indPlacar)
                glColor3f(1.0, 0, 0); //cor do texto
            else
                glColor3f(0, 0, 0); //cor do texto
            glRasterPos2f(45 + 5.5 * i, -60);
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, nome[i]);
        }
    }
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
    glutSpecialFunc(specialKeysPress);
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
void setMaterial_mont(void)
{
    //silver
    GLfloat objeto_ambient[] = { 0.19125f, 0.0735f, 0.0225f, 1.0f };
    GLfloat objeto_difusa[] = {0.7038f, 0.27048f, 0.0828f, 1.0f };
    GLfloat objeto_especular[] = {0.256777f, 0.137622f, 0.086014f, 1.0f };
    GLfloat objeto_brilho[] = {12.8f};

   glMaterialfv(GL_FRONT, GL_AMBIENT, objeto_ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, objeto_difusa);
   glMaterialfv(GL_FRONT, GL_SPECULAR, objeto_especular);
   glMaterialfv(GL_FRONT, GL_SHININESS, objeto_brilho);


}

void setMaterial_house(void)
{
    //silver
    GLfloat objeto_ambient[] = { 0.0f,0.0f,0.0f,1.0f };
    GLfloat objeto_difusa[] = { 0.55f,0.55f,0.55f,1.0f};
    GLfloat objeto_especular[] = {0.70f,0.70f,0.70f,1.0f };
    GLfloat objeto_brilho[] = {32.0f};

   glMaterialfv(GL_FRONT, GL_AMBIENT, objeto_ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, objeto_difusa);
   glMaterialfv(GL_FRONT, GL_SPECULAR, objeto_especular);
   glMaterialfv(GL_FRONT, GL_SHININESS, objeto_brilho);


}

void setMaterial_cannon(void)
{
    //silver
    GLfloat objeto_ambient[] = { 0.23125f, 0.23125f, 0.23125f, 1.0f };
    GLfloat objeto_difusa[] = {0.2775f, 0.2775f, 0.2775f, 1.0f };
    GLfloat objeto_especular[] = {0.773911f, 0.773911f, 0.773911f, 1.0f };
    GLfloat objeto_brilho[] = {89.6f};

   glMaterialfv(GL_FRONT, GL_AMBIENT, objeto_ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, objeto_difusa);
   glMaterialfv(GL_FRONT, GL_SPECULAR, objeto_especular);
   glMaterialfv(GL_FRONT, GL_SHININESS, objeto_brilho);


}

void display()
{
    if (pause)
    {
        return;//nao roda nada se estiver pausado
    }
    glDisable(GL_LIGHTING);
    int cor = fase % 2; //fase par tem uma cor impar tem outra
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    if (!comecou && !emPlacar)
    {

        inicio.draw((int)opcao);//faz o menu
    }
    else if (!comecou && emPlacar)
    {
        drawScore();//faz o score
    }
    else//roda o jogo normal
    {
        explosoes.desenhos();//desenha nossos tiros
        inimigos.desenhos();//desenha os tiros inimigos
        glEnable(GL_DEPTH_TEST); // Habilita Z-buffer
        glEnable(GL_CULL_FACE);  // Habilita Backface-Culling
        glEnable(GL_LIGHTING);
        /****Fundo****/
        glPushMatrix();
        setMaterial_mont();
        glTranslatef(-350,-24,-1500);
        glScalef(100,100,100);
        desenhaFaces(fundo);
        glPopMatrix();
        /************/

        //teste->draw(jogadorx, -jogadory,1.0,0.0,0.0);
        /*****   CIDADES   *****/
        setMaterial_house();
        int i = 3;
        inteira[10]=false;//nem uma cidade esta inteira
        for (int cd = -60; cd <= 240; cd += 50)
        {
            if (cd != 90)//nao desenha em baixo do canhao central
            {
                if (inteira[i])//se a cidade estiver inteira
                {
                    glPushMatrix();
                    glTranslatef(cd+5,-90,893);
                    desenhaFaces(cidade);
                    inteira[10]=true;//alguma cidade esta inteira
                    glPopMatrix();
                }
                i++;
            }
        }
        /***** FIM CIDADES *****/

        /******   CANHOES  *******/
        setMaterial_cannon();

        glPushMatrix();
        glRotated(90,1,0,0);
        glTranslatef(-81,-735,92);
        glScalef(0.1,0.1,0.1);
        desenhaFaces(cannon);
        glPopMatrix();


        glPushMatrix();
        glRotated(90,1,0,0);
        glTranslatef(97,-735,92);
        glScalef(0.1,0.1,0.1);
        desenhaFaces(cannon);
        glPopMatrix();


        glPushMatrix();
        glRotated(90,1,0,0);
        glTranslatef(276,-735,92);
        glScalef(0.1,0.1,0.1);
        desenhaFaces(cannon);
        glPopMatrix();

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
        glDisable(GL_LIGHTING);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);
        /*****    BALAS    *****/
        glColor3f(0, cor, 1);
        if (!inteira[2])
            explosoes.bala[2] = 0;
        for (int bl = 0; bl < explosoes.bala[2]; bl++)
        {
            glBegin(GL_QUADS);
            glVertex2f(86 + 3 * bl, -96.625);
            glVertex2f(84 + 3 * bl, -96.625);
            glVertex2f(84 + 3 * bl, -92.125);
            glVertex2f(86 + 3 * bl, -92.125);
            glEnd();
        }
        if (!inteira[0])
            explosoes.bala[0] = 0;
        for (int bl = 0; bl < explosoes.bala[0]; bl++)
        {
            glBegin(GL_QUADS);
            glVertex2f(-94 + 3 * bl, -96.625);
            glVertex2f(-96 + 3 * bl, -96.625);
            glVertex2f(-96 + 3 * bl, -92.125);
            glVertex2f(-94 + 3 * bl, -92.125);
            glEnd();
        }
        if (!inteira[1])
            explosoes.bala[1] = 0;
        for (int bl = 0; bl < explosoes.bala[1]; bl++)
        {
            glBegin(GL_QUADS);
            glVertex2f(264 + 3 * bl, -96.625);
            glVertex2f(262 + 3 * bl, -96.625);
            glVertex2f(262 + 3 * bl, -92.125);
            glVertex2f(264 + 3 * bl, -92.125);
            glEnd();
        }
        inicio.drawf(fase, pontos);
        drawAim();
    }
    glutSwapBuffers();
}

void keyboardPress(unsigned char key, int x, int y)
{
    if (!emPlacar)
    {
        switch (key)
        {
        case 27 :
            exit(0);
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
        case 13:
            if (!comecou && !opcao){
                comecou = true;
                }
            else if (!comecou && opcao)
                emPlacar = true;
            break;
        case 'p':
            pause = !pause;
            break;
        case 'r'://reseta todas variaveis
            fase = 1;
            pontos = 0;
            f = 0;
            inimigos.explo.clear();
            explosoes.explo.clear();
            inimigos.tam = 0;
            explosoes.tam = 0;
            for (int i = 0; i < 9; i++)
            {
                if (i < 3)
                    explosoes.bala[i] = 10;
                inteira[i] = true;
            }
            comecou=false;
            break;
        case 'z':
            pos-=1;
            break;
        case 'x':
            pos+=1;
            break;
        case 'c':
            cout<<pos<<endl;
            break;
        }

    }
    else
    {
        switch (key)
        {
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
        case 27 :
            exit(0);
            break;
        case 'r':
            fase = 1;
            pontos = 0;
            f = 0;
            inimigos.explo.clear();
            explosoes.explo.clear();
            inimigos.tam = 0;
            explosoes.tam = 0;
            emPlacar = false;
            for (int i = 0; i < 9; i++)
            {
                if (i < 3)
                    explosoes.bala[i] = 10;
                inteira[i] = true;
            }
            comecou=false;
            break;
        }
        if (!confirmaInsercao)
        {
            if (key == 13)
            {
                string str(nome);
                confirmaInsercao = true;
                pl->inserirJogador(nome, pontos);
                pl->salvarPontuacao();
            }
            else if (key == 8)
                nome[indPlacar] = ' ';
            if(indPlacar>0)
                indPlacar--;
        }
    }
}

void init()
{
    glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR);
    glClearColor(0.0, 0.2, 0.7, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100.0, 300, -100.0, 125, -900.0, 900.0);
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    // Cor da fonte de luz (RGBA)
    GLfloat cor_luz[] = {1.0, 1.0, 1.0, 1.0};
    // Posicao da fonte de luz. Ultimo parametro define se a luz sera direcional (0.0) ou tera uma posicional (1.0)
    GLfloat posicao_luz[] = {200.0, 200, 2000.0, 1.0};
    // Define parametros da luz
    glLightfv(GL_LIGHT0, GL_AMBIENT, cor_luz);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, cor_luz);
    glLightfv(GL_LIGHT0, GL_SPECULAR, cor_luz);
    glLightfv(GL_LIGHT0, GL_POSITION, posicao_luz);
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_FLAT);

    glLoadIdentity();
}
void mouse(int button, int state, int x, int y)
{
    if (pause)
    {
        return;
    }
    if (comecou)
    {
        if (button == GLUT_LEFT_BUTTON)
        {
            if (state == GLUT_DOWN)
            {
                mouseDown = true;
                float xreal = (float)(mousex / 2 - 100);
                float yreal = (float)(-1 * mousey / 2 + 125);
                if (xreal < 20 && explosoes.bala[0] > 0)//faz o canhao mais proximo atirar
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
    //rotationX += (float)(y - mousey);
    //rotationY += (float)(x - mousex);
    mousex = x;
    mousey = y;
}

void specialKeysPress(int key, int x, int y)
{

    if (!emPlacar)
    {
        switch (key)
        {
        case GLUT_KEY_UP:
            opcao = !opcao;
            break;
        case GLUT_KEY_DOWN:
            opcao = !opcao;
            break;
        case GLUT_KEY_RIGHT:
            break;
        case GLUT_KEY_LEFT:
            break;
        }
    }
    else
    {
        if (!confirmaInsercao)
        {
            switch (key)
            {
            case GLUT_KEY_UP:

                nome[indPlacar]++;
                if (nome[indPlacar] > 90)
                    nome[indPlacar] = 65;
                break;
            case GLUT_KEY_DOWN:
                nome[indPlacar]--;
                if (nome[indPlacar] < 65)
                    nome[indPlacar] = 90;
                break;
            case GLUT_KEY_RIGHT:

                if (indPlacar <= 18)
                    indPlacar++;
                if (nome[indPlacar] == ' ')
                    nome[indPlacar] = 65;
                break;
            case GLUT_KEY_LEFT:

                if (indPlacar >= 1)
                    indPlacar--;
                if (nome[indPlacar] == ' ')
                    nome[indPlacar] = 65;
                break;
            }
        }
    }
    glutPostRedisplay();
}
void idle()
{
    float t, dt;
    static float tLast = 0.0;
    /* Get elapsed time and convert to s */
    t = glutGet(GLUT_ELAPSED_TIME);
    t /= 300.0;
    /* Calculate delta t */
    if (pause)
    {
        tLast = t;
        return;
    }
    glutPostRedisplay();
    dt = t - tLast;
    explosoes.atualizaTempo(dt);
    inimigos.atualizaTempo(dt);
    //funcoes do professor para variacao de tempo a cima
    if (!comecou)
    {//idle no menu se precisar
    }
    else
    {
        jogadorx = (float)(mousex / 2 - 100);
        jogadory = (float)(-1 * mousey / 2 + 125);
        /***** MISSEIS *****/
        if (inteira[10] && f < fase)
            if (clok > 2)
            {
                f++;
                for (int i = 0; i < 3; i++)
                {
                    std::mt19937 rng(rand());
                    std::uniform_int_distribution<int> uni(-100, 300);
                    auto random_x = uni(rng);//x randomico
                    std::uniform_int_distribution<int> duni(0, 8);
                    auto cit = duni(rng);//cidade randomica
                    if (inteira[cit])//se a cidade ainda existir
                    {
                        if (cit == 2)
                        {
                            inimigos.addObjeto(100, -77.5, random_x, 125, 22000 - (fase * 2000), cit);
                        }
                        else if (cit == 0)
                        {

                            inimigos.addObjeto(-80, -77.5, random_x, 125, 22000 - (fase * 2000), cit);
                        }
                        else if (cit == 1)
                        {
                            inimigos.addObjeto(280, -77.5, random_x, 125, 22000 - (fase * 2000), cit);
                        }
                        else if (cit == 3)
                        {
                            inimigos.addObjeto(-50, -88.75, random_x, 125, 22000 - (fase * 2000), cit);
                        }
                        else if (cit == 4)
                        {
                            inimigos.addObjeto(0, -88.75, random_x, 125, 22000 - (fase * 2000), cit);
                        }
                        else if (cit == 5)
                        {
                            inimigos.addObjeto(50, -88.75, random_x, 125, 22000 - (fase * 2000), cit);
                        }
                        else if (cit == 6)
                        {
                            inimigos.addObjeto(150, -88.75, random_x, 125, 22000 - (fase * 2000), cit);
                        }
                        else if (cit == 7)
                        {
                            inimigos.addObjeto(200, -88.75, random_x, 125, 22000 - (fase * 2000), cit);
                        }
                        else if (cit == 8)
                        {
                            inimigos.addObjeto(250, -88.75, random_x, 125, 22000 - (fase * 2000), cit);
                        }
                    }
                    else
                        i--;
                }
                clok = 0;
            }
        pontos += inimigos.colisao(explosoes);//colide os inimigos com nossas explosoes
        pontos += inimigos.colisao(inimigos);//colide os inimigos com suas explosoes
        if (inteira[10])
            inimigos.dividir(inteira);//divide os misseis inimigos
        clok += dt;
        //std::cout<<inimigos.explo.size()<<std::endl;
        for (unsigned int i = 0; i < inimigos.explo.size(); i++)//verifica se a cidade esta sendo destruida
        {
            if (inimigos.explo[i].destruiu)
                if (inimigos.explo[i].alvo < 9)
                {
                    inteira[inimigos.explo[i].alvo] = false;
                }
        }
        if (fase == f && inimigos.explo.size() == 0)//passa de fase
        {
            fase++;
            f = 0;
            pontos += explosoes.bala[0] * 10;
            explosoes.bala[0] = 10;
            inteira[0] = true;
            pontos += explosoes.bala[1] * 10;
            explosoes.bala[1] = 10;
            inteira[1] = true;
            pontos += explosoes.bala[2] * 10;
            explosoes.bala[2] = 10;
            inteira[2] = true;
            clok = 1;
            for (int i = 0; i < 9; i++)
            {//conta ponto
                if (inteira[i])
                    pontos += 100;
            }
        }
    }
    if(!inteira[10]){//fim do jogo
        emPlacar=true;
        confirmaInsercao=false;
        comecou=false;
        inteira[10]=true;
    }

    tLast = t; //atualiza o tempo, deixar no fim da idle
}
