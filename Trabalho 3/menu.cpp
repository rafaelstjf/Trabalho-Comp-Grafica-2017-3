#include "menu.h"
#include <string>
#include <sstream>
#ifdef __linux__
#include <cstring>
#endif

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
void output(const char *string,float x,float y) //funcao para printar na tela
{
    glColor3f(0, 0, 0);     //cor do texto
    glRasterPos2f(x, y); //local
    int len, i;
    len = (int)strlen(string);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]); //printa com a fonte GLUT_BITMAP_TIMES_ROMAN_24
    }
}


menu::menu(){//inicializa as variaveis
animacao = 1;
cre = 0.1;

x[0]=120;
y[0]=90;

x[1]=120;
y[1]=20;

textureManager = new glcTexture();
    textureManager->SetNumberOfTextures(2);       // Estabelece o número de texturas que será utilizado
   textureManager->SetWrappingMode(GL_REPEAT);
    textureManager->CreateTexture("./marble.png", 0);
}

void menu::draw(int i)
{
    textureManager->Disable();
    glutSetCursor(GLUT_CURSOR_NONE);//sem mouse no menu
    glColor3f(1.0, 1.0, 1.0);
    glColor3f(0.0, 1.0, 0.0);// cor da caixa de seleçao
    //desenha a caixa de seleçao
    glLineWidth(4);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x[i]-10,y[i]+13);
    glVertex2f(x[i]+150,y[i]+13);
    glVertex2f(x[i]+150,y[i]-30);
    glVertex2f(x[i]-10,y[i]-30);
    glEnd();

    //escreve as coisas na tela
    //output("JOGAR",100,100);
    //output("PLACAR",100,50);
    //output("PRESSIONE ESC PARA SAIR",100,-50);
    //output("MISSILE",-50,100);
    //output("COMAND",-50,80);
        glColor3f(animacao/30, 0,1-animacao/30);//animacao da tela de menu
        glTranslatef(-2*animacao, -2*animacao, 0.0);
        glutSolidSphere(animacao, 20, 2);
    animacao+=cre;
    if(animacao>=30||animacao<=1)
    {
        cre*=-1;
    }

}

void menu::drawf(int f, int pontos){//durante o jogo
std::string print = "FASE:  "+patch::to_string(f);//escreve a fase
output(print.c_str(),-100,110);
print = "PONTOS: "+patch::to_string(pontos);//escreve os pontos
output(print.c_str(),-100,90);

}
