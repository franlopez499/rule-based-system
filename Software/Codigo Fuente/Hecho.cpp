

#include "Hecho.h"
#include <fstream>
using namespace std;

Hecho::Hecho()
{
    this->atributo = "-1";
    this->operador = "-1";
    this->valor = "-1";
}
Hecho::Hecho(string atributo, string operador, string valor)
{
    this->atributo = atributo;
    this->operador = operador;
    this->valor = valor;
}
Hecho::~Hecho()
{

}

void Hecho::printHecho(ofstream & filestream)
{
    filestream << atributo << " " << operador << " " << valor;
}

void Hecho::setAtributo(string atributo){
    this->atributo = atributo;
}
string Hecho::getAtributo(){
    return this->atributo;
}



void Hecho::setOperador(string operador){
    this->operador = operador;
}
string Hecho::getOperador(){
    return this->operador;
}


void Hecho::setValor(string valor){
    this->valor = valor;
}


string Hecho::getValor(){
    return this->valor;
}
