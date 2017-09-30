#ifndef MODELO_H
#define MODELO_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>

using namespace std;

class Modelo
{
private:
    typedef struct Lista
    {
        vector<int> elementos;
    } Lista;
    int tamVertices;
    int tamFaces;
    fstream arquivo;
    Lista** faces;
    double** vertices;
public:
    Modelo(string nomeArquivo);
    int getTamVertices();
    void exibirVertices();
    int getTamFaces();
    virtual ~Modelo();

};

#endif // MODELO_H
