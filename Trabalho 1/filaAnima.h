#ifndef FILAANIMA_H_INCLUDED
#define FILAANIMA_H_INCLUDED
#include "explosao.h"
#include <vector>
class filaAnima
{
public:
    filaAnima(int temp);
    void addObjeto(float x, float y, float initx, float inity, int bala);
    void atualizaTempo(float dt);
    void desenhos();
    int bala[3]={10,10,10};
private:
    int tempo;
    std::vector<explosao> explo;
    int tam = 0;
};
#endif // FILAANIMA_H_INCLUDED
