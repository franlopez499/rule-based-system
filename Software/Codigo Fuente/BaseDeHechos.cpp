#include "BaseDeHechos.h"
#include <iostream>
#include <string>
#include <utility>
#include <stdlib.h>
#include <algorithm>

BaseDeHechos::BaseDeHechos(ifstream &file)
{
    leerHechos(file);
}

BaseDeHechos::~BaseDeHechos()
{  
    
}


Hecho BaseDeHechos::getHecho(string objetivo){
    return hechos.find(objetivo)->second;
}
string BaseDeHechos::getObjetivo()
{
    return objetivo;
}
void BaseDeHechos::setObjetivo(string obj)
{
    objetivo = obj;
}
bool BaseDeHechos::contains(string objetivo)
{
    return hechos.find(objetivo) != hechos.end();
}


void BaseDeHechos::printBaseDeHechos(ofstream &filestream){
    filestream  << endl << "\t";
    for(auto &element : hechos)
    {
        filestream << "[";
        element.second.printHecho(filestream);
        filestream << "]" << endl<< "\t";
    }
    filestream << endl; 
   
}



unordered_map<string,Hecho> BaseDeHechos::getHechos()
{
    return hechos;
}


void BaseDeHechos::leerHechos(ifstream& fichero)
{
    int nHechos = 0; string tmp("");
    fichero >> nHechos;
    getline(fichero, tmp);

    for (int i = 0; i < nHechos; i++) {

        string atributo("");
        string op("");
        string valor("");

        fichero >> atributo;
        fichero >> op;
        fichero >> valor;
        toLower(atributo, valor);

        Hecho hecho(atributo, op, valor);
        addHecho(hecho);


        getline(fichero, tmp);
    }
    fichero.close();


  
}

void BaseDeHechos::toLower(string &atributo, string &valor) const {
    for_each(atributo.begin(), atributo.end(), [](char &c) {
        c = tolower(c);
    });

    for_each(valor.begin(), valor.end(), [](char &c) {
        c = tolower(c);
    });
}

void BaseDeHechos::addHecho(Hecho hecho)
{
    hechos.insert({hecho.getAtributo(),hecho});
}