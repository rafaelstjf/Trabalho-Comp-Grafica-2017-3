#ifndef FILAANIMA_H_INCLUDED
#define FILAANIMA_H_INCLUDED
#include "explosao.h"
#include <vector>
class filaAnima
{
public:
    filaAnima(int temp);
    void addObjeto(float x, float y, float initx, float inity,float vel = 100,int alvo = 10);//intancia explosoes
    void atualizaTempo(float dt);
    void desenhos(bool state);//desenha na tela
    int bala[3]={10,10,10};//inicia com 10 tiros
    int colisao(filaAnima ex);//controla colisao
    std::vector<explosao> explo;//vetor de explosoes
    int tam = 0;//tamanho do vector
    void dividir(bool inteira[]);//divide os misseis no topo da tela
private:

    int tempo;// controla o tempo
};
#endif // FILAANIMA_H_INCLUDED
