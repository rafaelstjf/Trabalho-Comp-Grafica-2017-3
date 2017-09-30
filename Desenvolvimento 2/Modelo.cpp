#include "Modelo.h"

Modelo::Modelo(string nomeArquivo)
{
    string linha;
    cout << "Abrindo arquivo: " << nomeArquivo << endl;
    arquivo.open(nomeArquivo, fstream::in); //Abre o arquivo
    if(arquivo.is_open()) //Se o arquivo estiver aberto comeca a leitura
    {
        arquivo.clear();
        getline(arquivo, linha);
        if(linha == "ply") //verifica se o arquivo realmente é um modelo
        {
            while(linha.find("element vertex"))  //procura a linha com o tamanho dos vertices
            {
                getline(arquivo, linha);
            }
            tamVertices = atoi((linha.substr(15)).c_str());
            while(linha.find("element face"))  //procura a linha com o tamanho das faces
            {
                getline(arquivo, linha);
            }
            tamFaces = atoi((linha.substr(12)).c_str());
            while(linha.find("end_header"))  //percorre o arquivo até o fim do cabecalho
            {
                getline(arquivo, linha);
            }
            vertices = new double*[tamVertices]; //aloca uma matriz de vertices do tamanho informado
            for(int i =0; i<tamVertices; i++)
            {
                vertices[i] = new double[3];
            }
            getline(arquivo, linha); //getline pra pular o end_header
            for(int i =0; i<tamVertices; i++)
            {
                arquivo >> vertices[i][1] >> vertices[i][2] >> vertices[i][3];
            }
            getline(arquivo, linha); //getline pra pular o ultimo vertice
            *faces = new Lista[tamFaces]; //cria um vetor do tipo lista com as faces do tamanho informado
            for(int i =0; i<tamFaces; i++)
            {

                //faces[i].elementos
            }

        }
        else
            cout << "Arquivo invalido!" << endl;
    }
    else
        cout << "Erro na abertura do arquivo!" << endl;
}
void Modelo::exibirVertices()  //funcao para verificacao/testes
{
    for(int i =0; i<tamVertices; i++)
    {
        for(int j = 0; j<3; j++)
            cout << vertices[i][j] << endl;
    }
}
Modelo::~Modelo()
{
    //dtor
}
