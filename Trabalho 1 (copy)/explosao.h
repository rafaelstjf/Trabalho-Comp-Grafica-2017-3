#ifndef EXPLOSAO_H_INCLUDED
#define EXPLOSAO_H_INCLUDED

class explosao
{
    public:
        explosao(float x, float y, float initx, float inity,int vel=1000);
        void desenhar();
        float tempo = 0,dt;
        float raio,linex,liney,x,y;
        int vel=4000,cont=0;
        bool colide=0;
    private:
        float dy,dx,cor=1,initx,inity;

};



#endif // EXPLOSAO_H_INCLUDED
