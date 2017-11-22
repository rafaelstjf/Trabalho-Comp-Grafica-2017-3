#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <GL/glut.h>
#include "glcTexture.h"
//classe para desenhar o menu
class menu{

public:
    menu();
    void draw(int i);//desenha o menu
    void drawf(int f,int pontos);//desenha o GUI no jogo
private:
    float x[2];
    float y[2];
    glcTexture* textureManager;
    float animacao,cre;

};

#endif // MENU_H_INCLUDED
