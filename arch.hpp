#ifndef ARCH_HPP_INCLUDED
#define ARCH_HPP_INCLUDED

#include <iostream>
#include "listascomp.hpp"
#include "listasordc.hpp"
using namespace std;


struct File{
    string id;
    // declaracion del dato (agregar de alguna forma)
    //Nodo<Dir> * carpeta = nullptr;  // esto en teoría no es necesario, porque se cuenta
    // con el puntero de la carpeta en la que se encuentra el archivo
};

struct Dir{
    string id;
    Dir * anterior = nullptr;
    Nodo<Dir> * sigs = nullptr;
    Nodo<File> * archs = nullptr;
};

// es conveniente utilizar esto en conjunto con la función mostrar
ostream& operator << (ostream &os , Dir d){
    os << d.id; 
    return os;
}


int criterio_carpeta(Dir a , Dir b){
    return a.id.compare(b.id);
}



void mkdir(string clav , Dir* curs){
    Dir mk;
    Nodo<Dir> * ck; // esto se encarga de chequear que una carpeta es única
    mk.id = clav;
    mk.anterior = curs;
    //agregar<Dir>(curs->sigs, mk);
    ck = buscar<Dir>( mk , curs->sigs , criterio_carpeta);
    if(ck == nullptr){
        insertar<Dir>(mk , curs->sigs , criterio_carpeta);
    }
    else{
        cout << "error: esa carpeta ya existe" << endl;
    }

}

void ls( Dir* curs){
    mostrar<Dir>(curs->sigs);
}



// esta función hay que implementarla luego de mkdir
//void mkfie(){}


void cd (string clav , Dir* &curs){
    if (clav == ".." && curs->anterior != nullptr){  // válido para todos los directorios salvo el inicial
        curs = curs->anterior; // se vuelve al directorio anterior
    }
    else{
        Dir mk;
        Nodo<Dir> * ck; // esto se encarga de chequear que una carpeta es única
        mk.id = clav;
        ck = buscar<Dir>( mk , curs->sigs , criterio_carpeta);
        if (ck == nullptr){
            cout << "error: no se encontró el directorio"<< endl;
        }
        
        else{
            curs = &ck->dato;
        }

    }
    
}



#endif // se incluye la librería de sistemas de archivos