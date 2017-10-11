#ifndef MISSILE_H_
#define MISSILE_H_

#include <GL/glut.h>

class missile{
private:
    int x, y;
    float color[3];
public:
    missile();
    void draw(int x, int y, float red, float green, float blue);
    ~missile();

};
#endif