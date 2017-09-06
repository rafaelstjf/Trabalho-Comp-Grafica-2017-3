#include "filaAnima.h"
#include <math.h>

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
        explo[i].dt=dt;
        explo[i].tempo+=dt;
        if(explo[i].tempo>(tempo/2)+1){
        explo[i].dt=-dt;
        }
    }
}

void filaAnima::desenhos()
{
    for(int i =0;i<tam;i++)
    {
            if(explo[i].tempo>tempo)
        {
            explo.erase(explo.begin()+i);
            tam--;
        }
        explo[i].desenhar();
    }
}
void filaAnima::colisao(filaAnima ex){
    for(int i =0;i<tam;i++)
    {
        float x =explo[i].linex;
        float y =explo[i].liney;
        for(int j =0;j<ex.tam;j++){
        if(ex.explo[j].colide){
            float x2 =ex.explo[j].linex;
            float y2 =ex.explo[j].liney;
            if(sqrt(pow(x-x2,2)+pow(y-y2,2))<ex.explo[j].raio+1){
                explo[i].x=x;
                explo[i].y=y;
                explo[i].cont+=explo[i].vel;
            }
        }
        }
    }
}
