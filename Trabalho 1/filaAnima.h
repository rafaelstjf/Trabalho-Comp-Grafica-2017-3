#ifndef FILAANIMA_H_INCLUDED
#define FILAANIMA_H_INCLUDED
#include "explosao.h"
#include <vector>
class filaAnima
{
public:
    filaAnima(int temp);
    void addObjeto(float x, float y, float initx, float inity,float vel = 400);
    void atualizaTempo(float dt);
    void desenhos();
    int bala[3]={10,10,10};
    void colisao(filaAnima ex);
    std::vector<explosao> explo;
    int tam = 0;
private:
    int tempo;
};
#endif // FILAANIMA_H_INCLUDED
