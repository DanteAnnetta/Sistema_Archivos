#include <iostream>
#include "listascomp.hpp"
#include "listasordc.hpp"
#include "arch.hpp"

using namespace std;


Dir home;
Dir * curs;
string path = "/home";


int main(){
    home.id = "home";
    curs = &home;
/*
    mkdir("c1" , curs);
    mkdir("c6" , curs);
    cd("c1" , curs , path);
    mkdir("c2" , curs);
    cd("c2" , curs , path);
    mkdir("c3" , curs);
    mkdir("c4" , curs);
    mkdir("c5" , curs);
    curs = curs->anterior;
    curs = curs->anterior;
    cd("c6" , curs , path);
    mkdir("c7" , curs);
    cd("c7" , curs , path);
    mkdir("c8" , curs);
    cd("c8" , curs , path);
    mkdir("c9" , curs);
    mkdir("c10" , curs);
*/
/*
    mkdir("dante" , curs);
    cd("dante" , curs , path);
    mkdir("c1" , curs);
    mkdir("c2" , curs);
    mkdir("c3" , curs);
    cd("c1" , curs , path);
    mkdir("bk" , curs);
    mkdir("c4" , curs);
    mkdir("c5" , curs);
    cd("c5" , curs , path);
    mkdir("dw" , curs);
*/

    mkdir("c1" , curs);
    mkdir("c2" , curs);
    mkdir("c3" , curs);
    mkdir("c4" , curs);
    cd("c1" , curs , path);
    mkdir("c5" , curs);
    mkdir("c6" , curs);
    mkdir("c7" , curs);
    curs = curs->anterior;
    cd("c2" , curs , path);
    mkdir("c8" , curs);
    curs = curs->anterior;
    cd("c3" , curs , path);
    mkdir("c9" , curs);
    cd("c9" , curs , path);
    mkdir("c10" , curs);
    cd("c10" , curs , path);
    mkdir("c11" , curs);
    mkdir("c12" , curs);
    curs = curs->anterior;
    curs = curs->anterior;
    curs = curs->anterior;
    cd("c4" , curs , path);
    mkdir("c13" , curs);
    cd("c13" , curs , path);
    mkdir("c14" , curs);
    mkdir("c15" , curs);
    cd("c15" , curs , path);
    mkdir("c16" , curs);



    // se crea un arbol genérico hasta acá-------------------------

    recorrer_arbol(&home);


    return 0;
}