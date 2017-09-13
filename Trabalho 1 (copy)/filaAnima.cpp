#include "filaAnima.h"
#include <math.h>
#include <random>
#include <time.h>

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
            if(sqrt(pow(x-x2,2)+pow(y-y2,2))<ex.explo[j].raio+2){
                explo[i].x=x;
                explo[i].y=y;
                explo[i].cont+=explo[i].vel;
            }
        }
        }
    }
}
void filaAnima::dividir(){
    int x,y;
     for(int i =0;i<tam;i++){
      if(explo[i].liney<100.1&&explo[i].liney>100){
        std::mt19937 rng(rand());
        std::uniform_int_distribution<int> uni(0, 100);
        auto percent = uni(rng);
        if(percent>99){
        for(int j=0;j<2;j++){
        std::uniform_int_distribution<int> duni(0, 8);
        auto cit = duni(rng);
        if(cit==1){x=100;y=-77.5;}
        else if(cit==0){x=-80;y=-77.5;}
        else if(cit==2){x=280;y=-77.5;}
        else if(cit==3){x=-50;y=-88.75;}
        else if(cit==4){x=-0;y=-88.75;}
        else if(cit==5){x=50;y=-88.75;}
        else if(cit==6){x=150;y=-88.75;}
        else if(cit==7){x=200;y=-88.75;}
        else if(cit==8){x=270;y=-88.75;}
        explo.push_back(explosao(x,y,explo[i].linex,explo[i].liney,3*explo[i].vel/4));
        tam++;
        }
        }
        }
     }

}
