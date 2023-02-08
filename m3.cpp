// el objetivo de este archivo es crear un intérprete de terminal sin necesidad de definir anteriormente la cantidad
// de parámetros que recibe cada comando, asmimismo como tampoco tener que comparar uno por uno todos ellos 

#include <iostream>
#include "listascomp.hpp"
#include "listasordc.hpp"
#include "arch.hpp"
#include <string.h>

using namespace std;

Dir home;
Dir * curs;
string path = "/home";
bool loop = true;
const int maxcom = 70;
char com[maxcom];
const char sp[2] = " "; // constante para poder separar los parámetros del comando
//Nodo<string> * params;

/*
string com;
string cl;
*/

int main(){
    // setup de las carpetas iniciales
    /*
    home.id = "home";
    curs = &home;
    mkdir("dante", curs);
    cd("dante", curs , path);
    mkdir("desktop" , curs);
    mkdir("docs" , curs);
    mkdir("downloads" , curs);
    */
    while (loop){
       // cout << curs->anterior->id<< "/" << curs->id << "@ ";
        cout << "/ ";
        cin.getline(com , maxcom , '\n');

        // esto se encarga de mostrar todos los caracteres que no son espacios
        string pal;
        for (int i = 0 ; i< maxcom ; i++){
            if (com[i] == sp[0]){ // si hay un espacio significa que es otro parámetro diferente
                //agregar<string>(params , pal); // agrega los parámetros a una cola
                cout << pal << endl;
                pal = "";
            }
            else{
                pal += com[i]; // concatena todos los caracteres no nulos
            }
            
        }
        if (pal != " "){
            //agregar<string>(params , pal);// último parámetro de la cola
            cout << pal << endl;
        }
        



    }

    return 0;
}