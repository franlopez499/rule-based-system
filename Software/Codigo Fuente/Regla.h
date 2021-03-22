#ifndef Regla_H
#define Regla_H

#include "Hecho.h"
#include <vector>
#include <fstream>
#include <utility>
#include <functional>


class Regla{
private:
    Hecho consecuente;
	vector<Hecho> antecedentes; // literal ó conjunción de literales
    int peso;
public:
    int identificador; //publico para la funcion hash

    Regla();
    Regla(int);
    ~Regla();
    int getNumLiterales();
    Hecho getConsecuente();
    int getPeso();
    vector<Hecho> getAntecedentes();
    int getIdentificador();
    void printRegla(ofstream &fs);
    void setIdentificador(int);
    void setPeso(int);
    void addAntecedente(Hecho);
    void setConsecuente(Hecho);
    bool operator ==(const Regla & obj) const;




};
namespace std {
        template <>
        class hash<Regla> {
            public:
            size_t operator()(const Regla &regla) const
            {
                std::hash<int> h;
                return h(regla.identificador);
            }
        };
}
#endif
