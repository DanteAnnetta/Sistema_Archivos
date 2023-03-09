#include <iostream>
#include "listascomp.hpp"
#include "listasordc.hpp"
#include "arch.hpp"

using namespace std;


Dir home;
Regdir rhome;
Dir * curs;
Nodo<Regdir>* listac; // lista que contendrá los datos de todas las carpetas (obtenido de archivo binario)

Nodo<Regdir>* buscaR; // puntero para hacer la asignación de los datos
string path = "/home";


int main(){

    rhome.anterior = "";
    rhome.id = "home";
    rhome.nivel = 0;
    insertar<Regdir>(rhome , listac , criterio_nivel);
    rhome.anterior = "home";
    rhome.id = "c1";
    rhome.nivel = 1;
    insertar<Regdir>(rhome , listac , criterio_nivel);
    rhome.anterior = "home";
    rhome.id = "c2";
    rhome.nivel = 1;
    insertar<Regdir>(rhome , listac , criterio_nivel);
    rhome.anterior = "home";
    rhome.id = "c3";
    rhome.nivel = 1;
    insertar<Regdir>(rhome , listac , criterio_nivel);
    rhome.anterior = "home";
    rhome.id = "c4";
    rhome.nivel = 1;
    insertar<Regdir>(rhome , listac , criterio_nivel);
    rhome.anterior = "c1";
    rhome.id = "c5";
    rhome.nivel = 2;
    insertar<Regdir>(rhome , listac , criterio_nivel);
    rhome.anterior = "c1";
    rhome.id = "c6";
    rhome.nivel = 2;
    insertar<Regdir>(rhome , listac , criterio_nivel);
    rhome.anterior = "c1";
    rhome.id = "c7";
    rhome.nivel = 2;
    insertar<Regdir>(rhome , listac , criterio_nivel);
    rhome.anterior = "c2";
    rhome.id = "c8";
    rhome.nivel = 2;
    insertar<Regdir>(rhome , listac , criterio_nivel);
    rhome.anterior = "c3";
    rhome.id = "c9";
    rhome.nivel = 2;
    insertar<Regdir>(rhome , listac , criterio_nivel);
    rhome.anterior = "c4";
    rhome.id = "c13";
    rhome.nivel = 2;
    insertar<Regdir>(rhome , listac , criterio_nivel);
    rhome.anterior = "c9";
    rhome.id = "c10";
    rhome.nivel = 3;
    insertar<Regdir>(rhome , listac , criterio_nivel);
    rhome.anterior = "c13";
    rhome.id = "c14";
    rhome.nivel = 3;
    insertar<Regdir>(rhome , listac , criterio_nivel);
    rhome.anterior = "c13";
    rhome.id = "c15";
    rhome.nivel = 3;
    insertar<Regdir>(rhome , listac , criterio_nivel);
    rhome.anterior = "c10";
    rhome.id = "c11";
    rhome.nivel = 4;
    insertar<Regdir>(rhome , listac , criterio_nivel);
    rhome.anterior = "c10";
    rhome.id = "c12";
    rhome.nivel = 4;
    insertar<Regdir>(rhome , listac , criterio_nivel);
    rhome.anterior = "c15";
    rhome.id = "c16";
    rhome.nivel = 4;
    insertar<Regdir>(rhome , listac , criterio_nivel);

    // carga de datos en la lista (simulación de carga-descarga desde un archivo binario)

// el punto de montaje siempre va a ser el primer elemento de la lista, por eso es que se agrega previo a utilizar 
    int buscan = 0;
    buscaR = obtener_siguiente(buscan , listac);
    buscan ++;
    home.id = buscaR->dato.id;
    home.nivel = buscaR->dato.nivel;
    curs = &home;
    
/*
    Nodo<Regdir>* aux = listac;
    while(aux){
        if(aux->dato.anterior == curs->id && aux->dato.nivel == curs->nivel + 1){ // 
            cout << aux->dato.id << "   " << aux->dato.nivel << "   " << aux->dato.anterior << endl;
        }
        
        aux = aux->sig;
    }
    cout << "-----------------------------------------------------" << endl;
    

*/

    recorrer_load(curs , listac);
    cout << "-----------------------------------------------------" << endl;

    recorrer_arbol(&home);  


    return 0;
}