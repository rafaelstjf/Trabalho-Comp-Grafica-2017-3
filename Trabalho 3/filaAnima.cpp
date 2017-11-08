#include "filaAnima.h"
#include <math.h>
#include <random>
#include <time.h>

filaAnima::filaAnima(int temp){//inicia a variavel tempo
    this->tempo = temp;
}
void filaAnima::addObjeto(float x, float y, float initx, float inity, float vel,int alvo)
{
    explo.push_back(explosao(x,y,initx,inity,vel,alvo));//instancia explosoes
    tam++;//aumenta o tamanho do vector
}
void filaAnima::atualizaTempo(float dt)
{
        for(int i =0;i<tam;i++)//percorre pelo vector
    {
        explo[i].dt=dt;//envia o dt
        explo[i].tempo+=dt;//incrementa o tempo
        if(explo[i].tempo>(tempo/2)+1){//faz a explosão diminuir depois de um tempo
        explo[i].dt=-dt;
        }
    }
}

void filaAnima::desenhos(bool state)
{
    for(int i =0;i<tam;i++)
    {
            if(explo[i].tempo>tempo)
        {
            explo.erase(explo.begin()+i);
            tam--;
        }
        explo[i].desenhar(state);
    }
}
int filaAnima::colisao(filaAnima ex){
    int pontos=0;
    for(int i =0;i<tam;i++)
    {
        float x =explo[i].linex;
        float y =explo[i].liney;
        for(int j =0;j<ex.tam;j++){
        if(!explo[i].falha)
        if(ex.explo[j].colide){
            float x2 =ex.explo[j].linex;
            float y2 =ex.explo[j].liney;
            if((sqrt(pow(x-x2,2)+pow(y-y2,2))+3<ex.explo[j].raio+2)||(sqrt(pow(x-x2,2)+pow(y-y2,2))-3<ex.explo[j].raio+2)){
                explo[i].x=x;
                explo[i].y=y;
                explo[i].cont+=explo[i].vel;
                explo[i].falha=1;
                pontos+=10;
            }
        }
        }
    }
    return pontos;
}
void filaAnima::dividir(bool inteira[]){
    int x,y;
     for(int i =0;i<tam;i++){
      if(explo[i].liney<100.1&&explo[i].liney>100){
        std::mt19937 rng(rand());
        std::uniform_int_distribution<int> uni(0, 100);
        auto percent = uni(rng);
        if(percent>80){
        for(int j=0;j<2;j++){
        std::uniform_int_distribution<int> duni(0, 8);
        auto cit = duni(rng);
        if(inteira[cit]){
        if(cit==2){x=100;y=-77.5;}
        else if(cit==0){x=-80;y=-77.5;}
        else if(cit==1){x=280;y=-77.5;}
        else if(cit==3){x=-50;y=-88.75;}
        else if(cit==4){x=0;y=-88.75;}
        else if(cit==5){x=50;y=-88.75;}
        else if(cit==6){x=150;y=-88.75;}
        else if(cit==7){x=200;y=-88.75;}
        else if(cit==8){x=250;y=-88.75;}
        explo.push_back(explosao(x,y,explo[i].linex,explo[i].liney,3*explo[i].vel/4,cit));
        tam++;
        }else j--;
        }
        }
        }
     }

}
