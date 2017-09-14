#include "Placar.h"
namespace patch //Correcao da funcao to_string
{
template <typename T>
std::string to_string(const T &n)
{
    std::ostringstream stm;
    stm << n;
    return stm.str();
}
}

//algoritmo de ordenacao para ordenar as posicoes do placar
void Placar::bubbleSort(Jogadores arr[], int n)
{
    int i, j;
    Jogadores aux;
    for (i = 0; i < n-1; i++)

        for (j = 0; j < n-i-1; j++)
            if (arr[j].pontuacao < arr[j+1].pontuacao)
            {
                aux = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = aux;
            }
}
/*
Construtor do placar
abre o arquivo e carrega os dados
*/
Placar::Placar()
{
    string linha;
    int i=0;
    ifstream input("Placar.txt");
    //arquivo.open("Placar.txt",fstream::in | fstream::trunc);
    if(input.is_open())
     {

       // arquivo.clear();
        while(input >> top10[i].nome >>  top10[i].pontuacao && i<10){
            i++;
        }
     }
     else
     {
         cout << "Erro na abertura do arquivo no arquivo de entrada!" <<endl;
         for(int k=0; k<10; k++){
            top10[k].nome = "DEV";
            top10[k].pontuacao = 0;
         }
     }
     input.close();
    bubbleSort(top10, 10);

}
//Retorna a pontuacao de uma determinada posicao
int Placar::getPontuacao(int i)
{
    return top10[i].pontuacao;
}

string Placar::getNome(int i)
{
    return top10[i].nome;
}
void Placar::inserirJogador(string nome, int pontuacao)
{
    Jogadores novo;
    novo.nome = nome;
    novo.pontuacao = pontuacao;
    bubbleSort(top10, 10);
    if(pontuacao > top10[9].pontuacao)
    {
        top10[9] = novo;
        bubbleSort(top10, 10);
    }

}

string Placar::getPosicao(int i )
{
    string posicao;
    posicao = top10[i].nome + "\t"+ patch::to_string(top10[i].pontuacao);
    return posicao;
}
void Placar::salvarPontuacao()
{
    string linha;
    arquivo.open("Placar.txt",fstream::out);
    if(arquivo.is_open())
    {

        for(int i =0; i<10; i++)
        {
            arquivo <<   top10[i].nome << "\t" << top10[i].pontuacao << endl;
        }
    }
    else
        cout << "Erro na abertura do arquivo de saida!" << endl;
        arquivo.close();
}

Placar::~Placar()
{
    //dtor
}
