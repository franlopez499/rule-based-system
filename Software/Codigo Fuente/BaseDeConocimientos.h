
#include "Regla.h"
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
class BaseDeConocimientos {

private:
    vector<Regla> reglas;
    string dominio;
    Hecho readHecho(ifstream &);
    void toLower(string &atributo, string &valor) const;

public:
    BaseDeConocimientos(ifstream&);
    ~BaseDeConocimientos();
    int getNumReglas();
    vector<Regla> &getReglas();
    void addRegla(Regla);
    void printBaseConocimientos(ofstream &);
    void readReglas(ifstream&);
    void setDominio(string);
    string getDominio();
    void setPeso(int,int);

};
