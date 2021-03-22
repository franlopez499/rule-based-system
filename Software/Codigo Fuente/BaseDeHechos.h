#ifndef BaseDeHechos_H
#define BaseDeHechos_H

#include <vector>
#include <fstream>
#include <unordered_map>
#include "Hecho.h"

class BaseDeHechos {
 private:

  unordered_map<string,Hecho> hechos;
  string objetivo;
  void toLower(string &atributo, string &valor) const;

public:
    BaseDeHechos(ifstream& file);
    ~BaseDeHechos();
    void addHecho(Hecho);
    Hecho getHecho(string);
    string getObjetivo();
    void setObjetivo(string);
    unordered_map<string,Hecho> getHechos();
    void printBaseDeHechos(ofstream &);
    void leerHechos(ifstream&);

    bool contains(string);
};

#endif
