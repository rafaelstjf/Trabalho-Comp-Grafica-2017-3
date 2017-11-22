#ifndef EXPLOSAO_H_INCLUDED
#define EXPLOSAO_H_INCLUDED

#include "Modelo.h"
#include "glcTexture.h"

class explosao
{
    public:
        explosao(float x, float y, float initx, float inity, int vel=1000, int alvo = 10);
        void desenhar(bool state);//desenha as explosoes
        float tempo = 0,dt;
        float raio,linex,liney,x,y;
        int vel=4000,cont=0, alvo;
        bool colide=0,falha=0,destruiu=0;
    private:
        void desenhaFace(Modelo *m);
        void setMaterial_missil();
        void setMaterial_explosao();
        float dy,dx,cor=1,initx,inity;
        glcTexture* textureManager;
        Modelo *missile= new Modelo("missile.ply", false);
        Modelo *explosion= new Modelo("explosion.ply", true);

};



#endif // EXPLOSAO_H_INCLUDED
