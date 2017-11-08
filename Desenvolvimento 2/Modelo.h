#ifndef MODELO_H
#define MODELO_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <math.h>
#ifndef _LINUX_
#include <cstring>
#endif
#define Branco 255
using namespace std;

class Modelo
{
private:
    int tamVertices;
    int tamFaces;
    fstream arquivo;
    int** faces;
    double** vertices;
    bool temCor = true;
    int** rgb;
    double** normalFlat;
    double** normalGouraud;
    bool gouraud;
public:
    Modelo(string nomeArquivo, bool gouraud);
    int getTamVertices();
    int** getFaces();
    double** getVertices();
    void exibirVertices();
    void exibirFaces();
    int getTamFaces();
    double** getNormalFlat();
    double** getNormalGouraud();
    bool getGouraud();
    int** getCor();
    float minx=999999,miny=999999,minz=999999,maxx=-999999,maxy=-999999,maxz=-999999;
    virtual ~Modelo();

};

#endif // MODELO_H
