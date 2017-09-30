#include "Modelo.h"

Modelo::Modelo(string nomeArquivo)
{
    cout << nomeArquivo << endl;
    string linha;
    arquivo.open(nomeArquivo, fstream::in);
    if(arquivo.is_open())
    {
        arquivo.clear();
        getline(arquivo, linha);
        if(linha == "ply")
        {
            while(linha.find("element vertex")){
                getline(arquivo, linha);
            }
           tamVertices = atoi((linha.substr(15)).c_str());
           while(linha.find("element face")){
                getline(arquivo, linha);
            }
            tamFaces = atoi((linha.substr(12)).c_str());
            while(linha.find("end_header")){
                getline(arquivo, linha);
            }
            vertices = new double*[tamVertices];
            for(int i =0; i<tamVertices; i++){
                    vertices[i] = new double[3];
            }
            getline(arquivo, linha);
            for(int i =0; i<tamVertices; i++){
                arquivo >> vertices[i][1] >> vertices[i][2] >> vertices[i][3];
            }
            getline(arquivo, linha);
            *faces = new Lista[tamFaces];
            for(int i =0; i<tamFaces; i++){

               //faces[i].elementos
            }

        }
        else
            cout << "Arquivo invalido!" << endl;
    }
    else
        cout << "Erro na abertura do arquivo!" << endl;
}
void Modelo::exibirVertices(){
       for(int i =0; i<tamVertices; i++){
                cout << vertices[i] << endl;
            }
}
Modelo::~Modelo()
{
    //dtor
}
