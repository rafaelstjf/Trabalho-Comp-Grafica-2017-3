#include "missile.h"

missile::missile(){
}
void missile::draw(int x1, int y1, float red, float green, float blue){
    glPushMatrix();
    x = x1;
    y = y1;
    color[1] = red;
    color[2] = blue;
    color[3] = green;
    glColor3f(red, green, blue);
    glBegin(GL_QUADS);
    glVertex2f(x, y+2);
    glVertex2f(x+2, y+2);
    glVertex2f(x+2, y);
    glVertex2f(x, y);
    glEnd();
    glPopMatrix();
}
missile::~missile(){
}
