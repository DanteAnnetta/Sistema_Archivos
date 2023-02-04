#include <iostream>
#include "listascomp.hpp"
#include "arch.hpp"

using namespace std;

// definiciones de las estructuras necesarias para esta primera prueba

Dir home; // carpeta maestra que almacena todos los demás directorios y archivos
Dir mk; // carpeta de asignación (para la carga de datos)
Dir* curs = nullptr; // puntero utilizado para desplazarse en todo el sistema de archivos (apunta a los directorios y no a los nodos)
string mv;


int main(){
    // declaraciones importantes previo a la manipulación de las estructuras
    home.id = "home";
    cout << home << " "; // borrar
    curs = &home; // "mount /home" el puntero apunta a la carpeta maestra

    for(int i = 1 ; i <10 ; i++){
        //mk.id = "usr" + to_string(i) ;
        mkdir("usr" + to_string(rand() % 10) , curs);
    }
    cout << "ls" << endl;
    ls(curs); // se muestran todas las carpetas de esta ubicación
    cout << endl << "cd ";
    cin >> mv;
    cd(mv , curs);

    




    return 0;
}