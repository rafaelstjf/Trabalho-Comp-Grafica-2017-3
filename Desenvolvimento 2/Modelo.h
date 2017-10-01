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
    int tamVertices;
    int tamFaces;
    fstream arquivo;
    int** faces;
    double** vertices;
public:
    Modelo(string nomeArquivo);
    int getTamVertices();
    int** getFaces();
    double** getVertices();
    void exibirVertices();
    void exibirFaces();
    int getTamFaces();
    virtual ~Modelo();

};

#endif // MODELO_H
