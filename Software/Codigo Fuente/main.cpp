

#include "MotorDeInferencia.h"
#include "Regla.h"
#include <fstream>
#include <string>
#include <iostream>



int main(int argc, char const *argv[])
{

    ifstream baseConocimientos(argv[1]);
    ifstream config(argv[2]);
    ifstream baseHechos(argv[3]);

    vector<ifstream*> streams = {&baseConocimientos, &config, &baseHechos};



    for (int i = 1; i <= 3; i++) {
        if (argv[i] == NULL) {
            cerr << "Número de argumentos incorrectos." << endl << "Uso: SBR.exe BaseDeConocimientos.txt ficheroConfiguracion.txt BaseDeHechos.txt" << endl;
            exit(1);
        }else if(!*streams[i-1])
        {
            cerr << "No se ha podido abrir el archivo -> \'" << argv[i] << "'" << endl;
            exit(1);
        }


    }
    string subcadena(argv[3]);
    subcadena= subcadena.substr(subcadena.find("-"));
    string salida1 = "Salida1" + subcadena;
    string salida2 = "Salida2" + subcadena;

    ofstream output1; ofstream output2;

    output1.open(salida1);
    output2.open(salida2);

    MotorDeInferencia *motor = new MotorDeInferencia(baseConocimientos, config, baseHechos);


    Hecho conclusion = motor->encaminamientoHaciaDelante(output1,output2);

    if (conclusion.getAtributo() == "-1") {
        output1 << "No se ha podido inferir ninguna solución a partir de los hechos." << endl;
        output2 << "No se ha podido inferir ninguna solución a partir de los hechos." << endl;
    }
    output1.close();
    output2.close();
    cout << "Ficheros obtenidos: "<< salida1 << " y "<< salida2 << endl;

    delete motor;

    return 0;
}