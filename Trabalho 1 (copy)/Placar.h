#ifndef PLACAR_H
#define PLACAR_H

#include <fstream>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <sstream>
using namespace std;

typedef struct Jogadores
{
    string nome;
    int pontuacao;

} Jogadores;
class Placar
{
public:
    Placar();
    ~Placar();
    void salvarPontuacao();
    void inserirJogador(string nome, int pontuacao);
    string getPosicao(int i);
    int getPontuacao(int i);
    string getNome(int i);
    void Teste();

private:
    Jogadores top10[10];
    fstream arquivo;
    void bubbleSort(Jogadores arr[], int n);

};

#endif // PLACAR_H
