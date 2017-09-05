#include "filaAnima.h"
#include <iostream>

filaAnima::filaAnima(int temp){
    this->tempo = temp;
}
void filaAnima::addObjeto(float x, float y, float initx, float inity, float vel)
{
    explo.push_back(explosao(x,y,initx,inity,vel));
    tam++;
}
void filaAnima::atualizaTempo(float dt)
{
        for(int i =0;i<tam;i++)
    {
        explo[i].tempo+=dt;
        explo[i].dt=dt;
    }
}

void filaAnima::desenhos()
{
    for(int i =0;i<tam;i++)
    {
            if(explo[0].tempo>tempo)
        {
            explo.erase(explo.begin());
            tam--;
        }
        explo[i].desenhar();
    }
}
void filaAnima::colisao(filaAnima ex){
    for(int i =0;i<tam;i++)
    {
        //explo[i].
    }
}
