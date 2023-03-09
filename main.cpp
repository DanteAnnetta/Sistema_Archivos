#include <iostream>
#include "listascomp.hpp"
#include "listasordc.hpp"
#include "arch.hpp"

using namespace std;


Dir home;
Regdir rhome;
Dir * curs;
Nodo<Regdir>* listac;
string path = "/home";


int main(){
    home.id = "home";
    home >> rhome;
    curs = &home;
    insertar<Regdir>(rhome , listac , criterio_nivel);

    mkdir("c1" , curs, listac);
    mkdir("c2" , curs, listac);
    mkdir("c3" , curs, listac);
    mkdir("c4" , curs, listac);
    cd("c1" , curs , path);
    mkdir("c5" , curs, listac);
    mkdir("c6" , curs, listac);
    mkdir("c7" , curs, listac);
    curs = curs->anterior;
    cd("c2" , curs , path);
    mkdir("c8" , curs, listac);
    curs = curs->anterior;
    cd("c3" , curs , path);
    mkdir("c9" , curs, listac);
    cd("c9" , curs , path);
    mkdir("c10" , curs, listac);
    cd("c10" , curs , path);
    mkdir("c11" , curs, listac);
    mkdir("c12" , curs, listac);
    curs = curs->anterior;
    curs = curs->anterior;
    curs = curs->anterior;
    cd("c4" , curs , path);
    mkdir("c13" , curs, listac);
    cd("c13" , curs , path);
    mkdir("c14" , curs, listac);
    mkdir("c15" , curs, listac);
    cd("c15" , curs , path);
    mkdir("c16" , curs, listac);




    // se crea un arbol genérico hasta acá-------------------------

    //recorrer_arbol(&home);

    
    cout << "Carpeta / Nivel / Anterior" << endl;
    mostrar<Regdir>(listac);




    return 0;
}