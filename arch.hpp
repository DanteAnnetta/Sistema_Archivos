#ifndef ARCH_HPP_INCLUDED
#define ARCH_HPP_INCLUDED

#include <iostream>
#include "listascomp.hpp"
#include "listasordc.hpp"
#include "disk.hpp"
using namespace std;



struct File{
    string id;
    int ini;
    int fin;
};

struct Dir{
    string id;
    Dir * anterior = nullptr;
    Nodo<Dir> * sigs = nullptr;
    Nodo<File> * archs = nullptr;
};

// es conveniente utilizar esto en conjunto con la función mostrar
ostream& operator << (ostream &os , Dir d){
    os << "  " << d.id; 
    return os;
}

ostream& operator << (ostream &os , File f){
    os << "  " << f.id; 
    return os;
}

int criterio_carpeta(Dir a , Dir b){
    return a.id.compare(b.id);
}

int criterio_arch(File a , File b){
    return a.id.compare(b.id);
}



void mkfile(string clav , Dir*curs , Nodo<File>* &listafls){
    File mf;
    Nodo<File> * ck;
    mf.id = clav;
    ck = buscar<File>(mf , curs->archs , criterio_arch);
    if(ck == nullptr){
        insertar<File>(mf , curs->archs , criterio_arch);
        push<File>(listafls , mf);
        crear_file(mf);
    }
    else{
        cout << "error: ya existe un archivo con este nombre" << endl;
    }
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

void rmdir(string clav , Dir* curs){
    Dir mk;
    Nodo<Dir> * ck;
    mk.id = clav;
    ck = buscar<Dir>(mk , curs->sigs , criterio_carpeta);
    if (!ck){
        cout << "error: no se encontro la carpeta" << endl;
    }
    else{
        if(mk.sigs != nullptr){
            borrar<Dir>(mk , curs->sigs , criterio_carpeta);
        }
        else{
            cout << "error: esta carpeta contiene otras carpetas adentro" << endl; // crear una forma recursiva de eliminarlas todas
        }
    }
}


void rmfile(string clav , Dir* curs, Nodo<File>* &listafls){
    File mf;
    Nodo<File> * ck;
    mf.id = clav;
    ck = buscar<File>(mf , curs->archs , criterio_arch);
    if (!ck){
        cout << "error: no se encontro el archivo" << endl;
    }
    else{
        borrar<File>(mf , curs->archs , criterio_arch);
        borrar<File>(mf , listafls , criterio_arch);
        eliminar_archivo( curs , clav, listafls);
    }
}




void ls( Dir* curs){
    mostrar<Dir>(curs->sigs);
    cout << endl;
    mostrar<File>(curs->archs);
}




void cd (string clav , Dir* &curs , string &path){
    if (clav == ".." && curs->anterior != nullptr){  // válido para todos los directorios salvo el inicial
        curs = curs->anterior; // se vuelve al directorio anterior
        string aux = curs->id;
        path.erase(path.length() - aux.length() - 1); // funciona pero bug (mientras más se usa peor funciona)
        
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
            path += "/" + curs->id;
        }

    }
    
}



#endif 
