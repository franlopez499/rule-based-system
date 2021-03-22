#include"Regla.h"
#include "Hecho.h"


Regla::Regla() {
    this->identificador = -1;
    peso = -1;

}

Regla::Regla(int identificador) {
    this->identificador = identificador;
    peso = -1;

}

Regla::~Regla() {

}

void Regla::printRegla(ofstream &filestream) {
    filestream << "R" << identificador;
    filestream << ": SI ";
    unsigned int i = 0;
    for (Hecho h : antecedentes) {
        h.printHecho(filestream);

        if(++i != antecedentes.size())
            filestream << " Y ";
    }
    filestream << " ENTONCES ";
    consecuente.printHecho(filestream);
    filestream << ";";
    filestream << " Peso: " << peso << endl;
}


void Regla::setPeso(int peso) {
    this->peso = peso;
}

int Regla::getPeso() {
    return this->peso;
}


void Regla::setIdentificador(int identificador) {
    this->identificador = identificador;
}

int Regla::getIdentificador() {
    return identificador;
}


void Regla::setConsecuente(Hecho consecuente) {
    this->consecuente = consecuente;
}

Hecho Regla::getConsecuente() {
    return consecuente;
}


void Regla::addAntecedente(Hecho antecedente) {
    antecedentes.push_back(antecedente);
}

vector<Hecho> Regla::getAntecedentes() {
    return this->antecedentes;
}

bool Regla::operator==(const Regla &obj) const {
    if (identificador == obj.identificador)
        return true;
    else
        return false;
}
