#include "Modelo.h"

Modelo::Modelo(string nomeArquivo)
{
    string linha;
    double n1[3];
    double n2[3];
    cout << "Abrindo arquivo: " << nomeArquivo << endl;
    arquivo.open(nomeArquivo, fstream::in); //Abre o arquivo
    if (arquivo.is_open())                  //Se o arquivo estiver aberto comeca a leitura
    {
        arquivo.clear();
        getline(arquivo, linha);
        if (linha.find("ply") != -1) //verifica se o arquivo realmente � um modelo
        {
            getline(arquivo, linha);
            if (linha.find("format ascii 1.0") != -1) //verifica se o arquivo esta no formato ascii
            {

                while (linha.find("element vertex") == -1 && arquivo.good()) //procura a linha com o tamanho dos vertices
                {

                    getline(arquivo, linha);
                }

                tamVertices = atoi((linha.substr(14)).c_str());
                while (linha.find("element face") == -1 && arquivo.good()) //procura a linha com o tamanho das faces
                {
                    getline(arquivo, linha);
                }

                tamFaces = atoi((linha.substr(13)).c_str());
                while (linha.find("end_header") == -1 && arquivo.good()) //percorre o arquivo at� o fim do cabecalho
                {
                    getline(arquivo, linha);
                }

                vertices = new double *[tamVertices]; //aloca uma matriz de vertices do tamanho informado
                for (int i = 0; i < tamVertices; i++)
                {
                    vertices[i] = new double[3];
                }
                for (int i = 0; i < tamVertices; i++)
                {
                    arquivo >> vertices[i][0] >> vertices[i][1] >> vertices[i][2];
                }
                faces = new int *[tamFaces]; //cria uma matriz de faces do tamanho informado
                for (int i = 0; i < tamFaces; i++)
                {
                    faces[i] = new int[4];
                }

                for (int i = 0; i < tamFaces; i++)
                {
                    //considerando que todos os ply tem 4 vertices
                    arquivo >> faces[i][0] >> faces[i][1] >> faces[i][2] >> faces[i][3];
                }

                normal = new double *[tamFaces];
                for (int i = 0; i < tamFaces; i++)
                {
                    normal[i] = new double[3];
                }
                for (int i = 0; i < tamFaces; i++)
                {
                    n1[0] = (vertices[faces[i][1]][1] * vertices[faces[i][2]][2] - vertices[faces[i][1]][2] * vertices[faces[i][2]][1]);
                    n1[1] = -1 * (vertices[faces[i][1]][0] * vertices[faces[i][2]][2] - vertices[faces[i][1]][2] * vertices[faces[i][2]][0]);
                    n1[2] = (vertices[faces[i][1]][0] * vertices[faces[i][2]][1] - vertices[faces[i][1]][1] * vertices[faces[i][2]][0]);

                    n2[0] = (vertices[faces[i][2]][1] * vertices[faces[i][3]][2] - vertices[faces[i][2]][2] * vertices[faces[i][3]][1]);
                    n2[1] = -1 * (vertices[faces[i][2]][0] * vertices[faces[i][3]][2] - vertices[faces[i][2]][2] * vertices[faces[i][3]][0]);
                    n2[2] = (vertices[faces[i][2]][0] * vertices[faces[i][3]][1] - vertices[faces[i][2]][1] * vertices[faces[i][3]][0]);
                    normal[i][0] =  (n1[1]*n2[2]-n1[2]*n2[2]);
                    normal[i][1] = -1 * ( n1[0]*n2[2] - n1[2]*n2[0]);
                    normal[i][2] = ( n1[0]*n2[1]-n1[1]*n2[0]);
                }
                cout << "Modelo carregado!" << endl;
            }
            else
                cout << "Arquivo nao esta no formato ascii 1.0!" << endl;
        }
        else
            cout << "Arquivo invalido!" << endl;
    }
    else
        cout << "Erro na abertura do arquivo!" << endl;
    arquivo.close();
}
void Modelo::exibirVertices() //funcao para verificacao/testes
{
    for (int i = 0; i < tamVertices; i++)
    {
        for (int j = 0; j < 3; j++)
            cout << vertices[i][j] << " ";
        cout << endl;
    }
}
void Modelo::exibirFaces()
{
    for (int i = 0; i < tamFaces; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << faces[i][j] << " ";
        }
        cout << endl;
    }
}
double **Modelo::getVertices()
{
    return vertices;
}
int **Modelo::getFaces()
{
    return faces;
}
int Modelo::getTamFaces()
{
    return tamFaces;
}
int Modelo::getTamVertices()
{
    return tamVertices;
}
double **Modelo::getNormal()
{
    return normal;
}
Modelo::~Modelo()
{

    delete[] vertices;
    delete[] faces;
}
