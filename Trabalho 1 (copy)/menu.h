#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <GL/glut.h>

class menu{

public:
    menu();
    void draw(int i);
private:
    float x[2];
    float y[2];
    float animacao,cre;

};

#endif // MENU_H_INCLUDED
