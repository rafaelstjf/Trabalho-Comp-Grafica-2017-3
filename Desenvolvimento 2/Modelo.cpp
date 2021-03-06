#include "Modelo.h"
#include <math.h>
Modelo::Modelo(string nomeArquivo, bool gouraud)
{
    this->gouraud = gouraud;
    string linha;
    double n1[3];
    double n2[3];
    //cout << "Abrindo arquivo: " << nomeArquivo << endl;
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
                        else if (count >= 3 && temCor && countrgb < 3)
                        {
                            rgb[i][countrgb] = atoi(temp.c_str());
                            countrgb++;
                        }
                        else if (countrgb >= 3 && count >= 3)
                        {
                            break;
                        }
                    }
                    if (vertices[i][0] < minx)
                        minx = vertices[i][0];
                    if (vertices[i][1] < miny)
                        miny = vertices[i][1];
                    if (vertices[i][2] < minz)
                        minz = vertices[i][2];

                    if (vertices[i][0] > maxx)
                        maxx = vertices[i][0];
                    if (vertices[i][1] > maxy)
                        maxy = vertices[i][1];
                    if (vertices[i][2] > maxz)
                        maxz = vertices[i][2];
                }
                maxx = (maxx - minx) / 2;
                maxy = (maxy - miny) / 2;
                maxz = (maxz - minz) / 2;
                for (int i = 0; i < tamVertices; i++)
                {
                    vertices[i][0] -= minx + maxx;
                    vertices[i][1] -= miny + maxy;
                    vertices[i][2] -= minz + maxz;
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

                normalFlat = new double *[tamFaces];
                for (int i = 0; i < tamFaces; i++)
                {
                    normalFlat[i] = new double[3];
                }
                for (int i = 0; i < tamFaces; i++)
                {
                    n1[0] = (vertices[faces[i][1]][0] - vertices[faces[i][2]][0]);
                    n1[1] = (vertices[faces[i][1]][1] - vertices[faces[i][2]][1]);
                    n1[2] = (vertices[faces[i][1]][2] - vertices[faces[i][2]][2]);
                    n2[0] = (vertices[faces[i][1]][0] - vertices[faces[i][3]][0]);
                    n2[1] = (vertices[faces[i][1]][1] - vertices[faces[i][3]][1]);
                    n2[2] = (vertices[faces[i][1]][2] - vertices[faces[i][3]][2]);

                    normalFlat[i][0] = (n1[1] * n2[2] - n1[2] * n2[1]);
                    normalFlat[i][1] = (n1[2] * n2[0] - n1[0] * n2[2]);
                    normalFlat[i][2] = (n1[0] * n2[1] - n1[1] * n2[0]);
                    float dist = sqrt(pow(normalFlat[i][0], 2) + pow(normalFlat[i][1], 2) + pow(normalFlat[i][2], 2));
                    normalFlat[i][0] = normalFlat[i][0] / dist;
                    normalFlat[i][1] = normalFlat[i][1] / dist;
                    normalFlat[i][2] = normalFlat[i][2] / dist;
                }
                if(gouraud)
                {
                    normalGouraud = new double*[tamVertices];
                    for(int i = 0; i<tamVertices; i++)
                        normalGouraud[i] = new double[3];
                    double nv1[3], nv2[3], nv3[3];
                    int numOcorrencias = 0;
                    for(int i = 0; i < tamVertices; i++)
                    {
                        for(int j = 0; j<tamFaces; j++)
                        {
                            for(int k = 0; k<3; k++)
                            {
                                if(i == faces[j][k])
                                {
                                    numOcorrencias++;
                                    if(numOcorrencias==1)
                                    {
                                        nv1[0] = normalFlat[j][0];
                                        nv1[1] = normalFlat[j][1];
                                        nv1[2] = normalFlat[j][2];
                                    }
                                    if(numOcorrencias==2)
                                    {
                                        nv2[0] = normalFlat[j][0];
                                        nv2[1] = normalFlat[j][1];
                                        nv2[2] = normalFlat[j][2];
                                    }
                                    if(numOcorrencias==3)
                                    {
                                        nv3[0] = normalFlat[j][0];
                                        nv3[1] = normalFlat[j][1];
                                        nv3[2] = normalFlat[j][2];
                                    }
                                }
                            }
                        }
                        normalGouraud[i][0] = ((nv1[0]+nv2[0]+nv3[0])/3);
                        normalGouraud[i][1] = ((nv1[1]+nv2[1]+nv3[1])/3);
                        normalGouraud[i][2] = ((nv1[2]+nv2[2]+nv3[2])/3);
                        numOcorrencias = 0;

                    }
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
double** Modelo::getNormalFlat()
{
    return normalFlat;
}
double** Modelo::getNormalGouraud()
{
    return normalGouraud;
}
int **Modelo::getCor()
{
    return rgb;
}
bool Modelo::getGouraud()
{
    return gouraud;
}
Modelo::~Modelo()
{

    delete[] vertices;
    delete[] faces;
}
