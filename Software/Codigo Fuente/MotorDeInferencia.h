#ifndef MotorDeInferencia_H
#define MotorDeInferencia_H

#include "BaseDeConocimientos.h"
#include "BaseDeHechos.h"
#include <unordered_map>
#include <unordered_set>

class MotorDeInferencia {

public:
	MotorDeInferencia(ifstream&,ifstream&,ifstream&);
    ~MotorDeInferencia();
    Hecho encaminamientoHaciaDelante(ofstream &,ofstream &);
    unordered_map<string,unordered_map<string,string>> getArgumentos();
private:
    BaseDeConocimientos bc;
    BaseDeHechos bh;
    void readConfig(ifstream &);
    bool comprobarAntecedentes(Regla);
    bool isInBaseHechos(Hecho);
    Regla Resolver(unordered_set <Regla> &);
    void equiparar(unordered_set <Regla>& ,unordered_set <Regla>&, ofstream &);
    unordered_map<string,unordered_map<string,string>> argumentos; // atributo -> {tipo, valores de su dominio}
    void toLower(string &atributo, string &tipo, string &dominio) const;
};

#endif
