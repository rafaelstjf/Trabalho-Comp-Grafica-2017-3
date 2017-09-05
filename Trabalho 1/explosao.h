#ifndef EXPLOSAO_H_INCLUDED
#define EXPLOSAO_H_INCLUDED

class explosao
{
    public:
        explosao(float x, float y, float initx, float inity,int vel=4000);
        void desenhar();
        float tempo = 0,dt;
    private:
        float raio,x,y,linex,liney,dy,dx,cor=1,initx,inity;
        int vel=4000,cont=0;
};



#endif // EXPLOSAO_H_INCLUDED
