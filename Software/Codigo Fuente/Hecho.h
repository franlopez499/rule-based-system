#ifndef Hecho_H
#define Hecho_H

#include <string>
using namespace std;

class Hecho {
  	
private:
    string atributo;
    string operador;
    string valor;
    
public:
    Hecho();
    Hecho(string,string,string);
    ~Hecho();
    void printHecho(ofstream &);
    string getAtributo();
    string getOperador();
    string getValor();
    void setAtributo(string);
    void setOperador(string);
    void setValor(string);



};

#endif