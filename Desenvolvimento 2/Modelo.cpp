#include "Modelo.h"
#include <math.h>
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
                while (linha.find("end_header") == -1 && arquivo.good())
                {
                    if (linha.find("element vertex") != -1)
                        tamVertices = atoi((linha.substr(14)).c_str());
                    else if (linha.find("element face") != -1)
                        tamFaces = atoi((linha.substr(13)).c_str());
                    else if (linha.find("property uchar red") != -1 || linha.find("R ") != -1)
                        temCor = true;
                    getline(arquivo, linha);
                }
                vertices = new double *[tamVertices]; //aloca uma matriz de vertices do tamanho informado
                rgb = new int *[tamVertices];         //aloca uma matriz de vertices do tamanho informado
                for (int i = 0; i < tamVertices; i++)
                {
                    vertices[i] = new double[3];
                    rgb[i] = new int[3];
                }
                for (int i = 0; i < tamVertices; i++)
                {
                    for (int j = 0; j < 3; j++)
                        rgb[i][j] = Branco;
                }
                for (int i = 0; i < tamVertices; i++)
                {
                    int count = 0;
                    int countrgb = 0;
                    string temp;
                    getline(arquivo, linha);
                    stringstream ss(linha);
                    while (getline(ss, temp, (char)32))
                    {
                        if (count < 3)
                        {
                            vertices[i][count] = atof(temp.c_str());
                            count++;
                        }
                        else
                             if(count>=3 && temCor){
                            rgb[i][countrgb] = atoi(temp.c_str());
                            countrgb++;
                        }
                    }
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
<<<<<<< HEAD
                    n1[0] = (vertices[faces[i][1]][0] * vertices[faces[i][3]][0]+vertices[faces[i][1]][1] * vertices[faces[i][3]][1]+vertices[faces[i][1]][2] * vertices[faces[i][3]][2])*vertices[faces[i][2]][0];
                    n1[1] =(vertices[faces[i][1]][0] * vertices[faces[i][3]][0]+vertices[faces[i][1]][1] * vertices[faces[i][3]][1]+vertices[faces[i][1]][2] * vertices[faces[i][3]][2])*vertices[faces[i][2]][1];
                    n1[2] = (vertices[faces[i][1]][0] * vertices[faces[i][3]][0]+vertices[faces[i][1]][1] * vertices[faces[i][3]][1]+vertices[faces[i][1]][2] * vertices[faces[i][3]][2])*vertices[faces[i][2]][3];

                    n2[0] = (vertices[faces[i][1]][0] * vertices[faces[i][2]][0]+vertices[faces[i][1]][1] * vertices[faces[i][2]][1]+vertices[faces[i][1]][2] * vertices[faces[i][2]][2])*vertices[faces[i][3]][0];
                    n2[1] =(vertices[faces[i][1]][0] * vertices[faces[i][2]][0]+vertices[faces[i][1]][1] * vertices[faces[i][2]][1]+vertices[faces[i][1]][2] * vertices[faces[i][2]][2])*vertices[faces[i][3]][1];
                    n2[2] = (vertices[faces[i][1]][0] * vertices[faces[i][2]][0]+vertices[faces[i][1]][1] * vertices[faces[i][2]][1]+vertices[faces[i][1]][2] * vertices[faces[i][2]][2])*vertices[faces[i][3]][3];

                    normal[i][0] = n1[0]-n2[0];
                    normal[i][1] = n1[1]-n2[1];
                    normal[i][2] = n1[2]-n2[2];
=======
                    n1[0] = (vertices[faces[i][1]][0] - vertices[faces[i][2]][0]);
                    n1[2] = (vertices[faces[i][1]][1] - vertices[faces[i][2]][1]);
                    n1[1] = (vertices[faces[i][1]][2] - vertices[faces[i][2]][2]);


                    n2[0] = (vertices[faces[i][1]][0] - vertices[faces[i][3]][0]);
                    n2[2] = (vertices[faces[i][1]][1] - vertices[faces[i][3]][1]);
                    n2[1] = (vertices[faces[i][1]][2] - vertices[faces[i][3]][2]);

                    normal[i][0] = (n1[1] * n2[2] - n1[2] * n2[1]);
                    normal[i][1] = (n1[2] * n2[0] - n1[0] * n2[2]);
                    normal[i][2] = (n1[0] * n2[1] - n1[1] * n2[0]);
>>>>>>> 5be959e2e02854835e62b0daf28e7dd15255725f
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
int **Modelo::getCor()
{
    return rgb;
}
Modelo::~Modelo()
{

    delete[] vertices;
    delete[] faces;
}
