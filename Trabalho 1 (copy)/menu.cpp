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


menu::menu(){
animacao = 1;
cre = 0.1;

x[0]=100;
y[0]=100;

x[1]=100;
y[1]=50;

}

void menu::draw(int i)
{
    glColor3f(0.0, 0.0, 1.0);
    //quadrado
    glBegin(GL_LINE_LOOP);
    glVertex2f(x[i]-10,y[i]+13);
    glVertex2f(x[i]+100,y[i]+13);
    glVertex2f(x[i]+100,y[i]-5);
    glVertex2f(x[i]-10,y[i]-5);
    glEnd();
    output("JOGAR",100,100);
    output("PLACAR",100,50);
    output("PRECIONE ESC PARA SAIR",100,-50);
    output("MISSILE",-50,100);
    output("COMAND",-50,80);
        glColor3f(animacao/30, 0,1-animacao/30);
        glTranslatef(-2*animacao, -2*animacao, 0.0);
        glutSolidSphere(animacao, 20, 2);
    animacao+=cre;
    if(animacao>=30||animacao<=1)
    {
        cre*=-1;
    }

}
