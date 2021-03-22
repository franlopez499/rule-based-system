

#include <unordered_set>
#include "MotorDeInferencia.h"
#include "Regla.h"
#include <string>
#include <iostream>
#include <fstream>
#include <limits.h>
#include <algorithm>

using namespace std;


MotorDeInferencia::MotorDeInferencia(ifstream &f_bc, ifstream &f_config, ifstream &f_bh) : bc(f_bc), bh(f_bh) {

    readConfig(f_config);

}

MotorDeInferencia::~MotorDeInferencia() {

}
unordered_map<string,unordered_map<string,string>> MotorDeInferencia::getArgumentos()
{
    return argumentos;

}
void MotorDeInferencia::readConfig(ifstream &fileConfig) {


    string tmp;
    string atributo, tipo;
    int nAtributos;
    getline(fileConfig, tmp);
    fileConfig >> nAtributos;

    for (int i = 0; i < nAtributos; i++) {
        fileConfig >> atributo;
        fileConfig >> tipo;


        if (tipo != "NU") {
            string dominio;
            fileConfig >> dominio;
            dominio = dominio.substr(1, dominio.size() - 2);
            toLower(atributo, tipo, dominio);

            argumentos[atributo].insert({tipo, dominio});

        } else {
            string vacio = "";
            toLower(atributo, tipo, vacio);
            argumentos[atributo].insert({tipo, vacio});
        }
    }

    getline(fileConfig, atributo);
    getline(fileConfig, atributo);
    string objetivo;

    getline(fileConfig, objetivo);

    for_each(objetivo.begin(), objetivo.end(), [](char &c) {
        c = tolower(c);
    });

    if(objetivo[objetivo.size() - 1] == '\r'){
        objetivo.erase(objetivo.size() - 1);
    }
    bh.setObjetivo(objetivo);


    getline(fileConfig, tmp);

    string nReglas;
    getline(fileConfig, nReglas);

    int numReglas = atoi(nReglas.c_str());
    for (int i = 0; i < numReglas; i++) {
        getline(fileConfig, tmp);
        bc.getReglas()[i].setPeso(atoi(tmp.c_str()));
    }

    fileConfig.close();

}

void MotorDeInferencia::toLower(string &atributo, string &tipo, string &dominio) const {
    for_each(atributo.begin(), atributo.end(), [](char &c) {
        c = tolower(c);
    });

    for_each(tipo.begin(), tipo.end(), [](char &c) {
        c = tolower(c);
    });
    for_each(dominio.begin(), dominio.end(), [](char &c) {
        c = tolower(c);
    });
}


bool MotorDeInferencia::isInBaseHechos(Hecho hecho) {
    bool flag = false;
    for (auto ele : bh.getHechos()) {
        if (hecho.getAtributo() == ele.first) {
            if ((hecho.getOperador() == "=") && (hecho.getValor() == ele.second.getValor())) {
                flag = true;
            } else if (hecho.getOperador() == "<") {
                flag = atoi(ele.second.getValor().c_str()) < atoi(hecho.getValor().c_str());
            } else if (hecho.getOperador() == ">") {
                flag = atoi(ele.second.getValor().c_str()) > atoi(hecho.getValor().c_str());
            } else if (hecho.getOperador() == "<=") {
                flag = atoi(ele.second.getValor().c_str()) <= atoi(hecho.getValor().c_str());
            } else if (hecho.getOperador() == ">=") {
                flag = atoi(ele.second.getValor().c_str()) >= atoi(hecho.getValor().c_str());
            }

            if (flag)
                return true;

        }

    }

    return false;
}

bool MotorDeInferencia::comprobarAntecedentes(Regla regla) {
    for (unsigned int i = 0; i < regla.getAntecedentes().size(); i++) {
        if (!isInBaseHechos(regla.getAntecedentes()[i]))
            return false;
    }
    return true;
}

/*
* Devuelve por argumento el conjunto conflicto con las nuevas reglas que se pueden disparar a partir de la base de hechos actual.
*/
void MotorDeInferencia::equiparar(unordered_set<Regla> &conjuntoConflicto, unordered_set<Regla> &reglasAplicadas,
                                  ofstream &f) {

    f << "-FASE DE EQUIPARACION-CONJUNTO CONFLICTO-" << endl << endl;

    bool inserta = false;
    for (int i = 0; i < bc.getNumReglas(); i++) {
        //Comprobar que no se ha usado ya y que se puede inferir algo
        if (reglasAplicadas.find(bc.getReglas()[i]) == reglasAplicadas.end() &&
            comprobarAntecedentes(bc.getReglas()[i])) {


            auto it = conjuntoConflicto.insert(bc.getReglas()[i]);
            inserta = it.second;
            if (it.second) {
                Regla a = *it.first;
                f << "\tSE INSERTA EN EL CONJUNTO CONFLICTO: " << endl << "\t->";
                a.printRegla(f);
                f << endl;
            }
        }
    }

    if(!inserta)
    {
        f << "\t->Ninguna regla insertada en el conjunto conflicto\n\n";
    }

    f << "-FIN FASE EQUIPARACION-CONJUNTO CONFLICTO-" << endl << endl;


}

/*
* Devuelve regla elegida para ser disparada tras resolver el conflicto dentro del conjunto conflicto según un criterio estático de prioridades de
* mayor a menor, en caso de empate se devuelve la de menor identificador de regla.
*/
Regla MotorDeInferencia::Resolver(unordered_set<Regla> &conjuntoConflicto) {

    Regla maxRegla(INT_MAX);
    for (Regla regla : conjuntoConflicto) {
        if (regla.getPeso() > maxRegla.getPeso()
            || ((regla.getPeso() == maxRegla.getPeso()) && (regla.getIdentificador() < maxRegla.getIdentificador()))) {
            maxRegla = regla;
        }
    }

    return maxRegla;


}

Hecho MotorDeInferencia::encaminamientoHaciaDelante(ofstream &f, ofstream &f1) {

    unordered_set<Regla> reglasAplicadas;
    unordered_set<Regla> conjuntoConflicto;
    vector<Regla> ordenReglas;
    f << "-DOMINIO DE LA APLICACIÓN-"<< endl;
    f << "\t->"<<bc.getDominio()<< endl << endl;

    f1 << "-DOMINIO DE LA APLICACIÓN-"<< endl;
    f1 << "\t->"<<bc.getDominio()<< endl << endl;

    f << "-OBJETIVO-" << endl;
    f << "\t->" << bh.getObjetivo() << endl << endl;

    f1 << "-OBJETIVO-" << endl;
    f1 << "\t->" << bh.getObjetivo() << endl << endl;

    f << "BASE DE HECHOS INICIAL:";
    bh.printBaseDeHechos(f);
    f << endl << endl;


    Regla r;
    do {
        conjuntoConflicto.erase(r);
        equiparar(conjuntoConflicto, reglasAplicadas, f); // rellenamos el conjuntoConflicto

        if (!conjuntoConflicto.empty()) {
            r = Resolver(conjuntoConflicto); // regla a disparar

            f << "-FASE RESOLVER-\n\n";
            // Imprimir regla seleccionada a disparar
            f << "-Regla disparada-" << endl << "\t->";
            r.printRegla(f);
            f << endl << endl;
            f << "-FIN FASE RESOLVER-\n\n";
            // Fase Aplicar
            Hecho nuevoHecho = r.getConsecuente();

            reglasAplicadas.insert(r);
            ordenReglas.push_back(r);

            bh.addHecho(nuevoHecho);
            f << "BASE DE HECHOS ACTUALIZADA:";
            bh.printBaseDeHechos(f);
        }

    }while(!conjuntoConflicto.empty() && !bh.contains(bh.getObjetivo()));


    if (bh.contains(bh.getObjetivo())) {
        //Devolvemos el �ltimo hecho deducido ya que es la soluci�n
        Hecho final = bh.getHecho(bh.getObjetivo());
        f << "Se ha encontrado solución tras aplicar las siguientes reglas: " << endl;
        f1 << "Se ha encontrado solución tras aplicar las siguientes reglas: " << endl;

        for(Regla ra : ordenReglas){
            f << "\t->";
            f1 << "\t->";

            ra.printRegla(f);
            ra.printRegla(f1);
        }

        f << "Solucion inferida: ";
        f1 << "Solucion inferida: ";

        final.printHecho(f);
        final.printHecho(f1);
        return final;


    } else return Hecho("-1", "-1", "-1");


}



