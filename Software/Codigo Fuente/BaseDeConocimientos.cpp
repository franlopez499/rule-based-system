#include "BaseDeConocimientos.h"
#include <fstream>

using namespace std;

BaseDeConocimientos::BaseDeConocimientos(ifstream &file)
{
    
    readReglas(file);
}

BaseDeConocimientos::~BaseDeConocimientos()
{

}

int BaseDeConocimientos::getNumReglas()
{
    return reglas.size();
}


void BaseDeConocimientos::setPeso(int pos,int peso)
{
    reglas[pos] = peso;
}
void BaseDeConocimientos::addRegla(Regla regla)
{
    reglas.push_back(regla);
}

vector<Regla>& BaseDeConocimientos::getReglas(){
    return reglas;
}
void BaseDeConocimientos::printBaseConocimientos(ofstream &filestream)
{
   
    filestream << "BC: " << dominio << endl << endl;
    filestream << "ID PRIORIDAD" << endl;
    

    for(Regla regla : reglas){
        regla.printRegla(filestream);
    }
    filestream <<endl;
}

Hecho BaseDeConocimientos::readHecho(ifstream &in){
    string atributo("");
    string op("");
    string valor("");

    in >> atributo;
    in >> op;
    in >> valor;
    toLower(atributo, valor);

    Hecho hecho(atributo,op,valor);
    return hecho;
}

void BaseDeConocimientos::toLower(string &atributo, string &valor) const {
    for_each(atributo.begin(), atributo.end(), [](char &c) {
        c = tolower(c);
    });

    for_each(valor.begin(), valor.end(), [](char &c) {
        c = tolower(c);
    });
}

void BaseDeConocimientos::setDominio(string dom)
{

    dominio = dom;

}


string BaseDeConocimientos::getDominio()
{
    return dominio;
}

void BaseDeConocimientos::readReglas(ifstream& in)
{

    //ifstream in(f_bc);
    string tmp;
    int nReglas;

    getline(in,tmp);
    setDominio(tmp);
    
    in >> nReglas;

    for(int i = 0; i < nReglas; i++){
        Regla regla;
        regla.setIdentificador(i+1);
        in >> tmp;//getline(in, tmp, ' ');
        in >> tmp; // saltar Si
        
        
        regla.addAntecedente(readHecho(in));

        //in >> tmp;
        
  
        do{
            in >> tmp;
            if(tmp == "y"){
                regla.addAntecedente(readHecho(in));
            }else if(tmp == "Entonces"){
                regla.setConsecuente(readHecho(in));
                addRegla(regla);
                //break;
            }

        }while(tmp == "y");


    }
    in.close();
    
}