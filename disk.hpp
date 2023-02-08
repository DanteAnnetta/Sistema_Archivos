#ifndef DISK_HPP_INCLUDED
#define DISK_HPP_INCLUDED
// esta es la librería que permite controlar el archivo binario "disk.bin" como si fuera una suerte de disco duro

// agregar una lista de archivos 

#include<iostream>
#include<fstream>
#include "rwstring.hpp"
#include "arch.hpp"
#include "listascomp.hpp"
#include "listasordc.hpp"

using namespace std;

const int lline = 180;  // cantidad máxima de caracteres definida por cada linea
char lin[lline];        // esto podría moverse a la función de escritura

struct Line{
    string cont;
};

ostream& operator << (ostream & os , Line l){
    os << l.cont;
    return os;
}
// lectura
fstream& operator >> (fstream& fs , Line& l){
    l.cont = readstring(fs , lline);
    return fs;
}
// escritura
fstream& operator << (fstream& fs , Line l){
    writestring(fs , l.cont , lline);
    return fs;
}


/*
void eliminar_archivo( Dir*curs, string clav ,  Nodo<File>* lista){
    Line aux;
    File mf;
    mf.id = clav;
    Nodo<File>* f;
    Nodo<File>* p = lista;
    f = buscar<File>(mf , curs->archs , criterio_arch);

*/


void mostrar_archivo (Dir* curs, string clav , Nodo<File>* lista){   // función para leer el contenido de un archivo
    Line aux;
    File mf;
    mf.id = clav;
    Nodo<File>* f;
    f = buscar<File>(mf , curs->archs , criterio_arch);
    fstream file1;
    file1.open("disk.bin" , ios::binary | ios::in);
    if(!file1){
        cout << "Error: no se pudo abrir el archivo" << endl;
    }
    int i = 0;
    while(file1 >> aux){
        if (i -1 > f->dato.ini && i -1 < f->dato.fin){  
            cout << aux.cont << endl;
        }
        i ++;
    }
    file1.close();

}

void crear_file(File & f){
    Line aux;
    fstream file1;
    int ini = 0;
    int fin;
    file1.open("disk.bin" , ios::binary | ios::out);
    while(file1 >> aux){
        ini++;
    }
    f.ini = ini; // se registra a partir de que linea comienza el archivo
    fin = ini;
    file1.close();
    
    file1.open("disk.bin" , ios::binary | ios::app);

    string dat = "";
    while (dat!=":q"){
        cout << "/" ;
        cin.getline(lin , lline , '\n');
        for(int i = 0; i< lline ;i++){
            dat += lin[i];
        }
        aux.cont = dat;
        file1 << aux;
        aux.cont = "";
        dat = "";

        fin++;
    }
    f.fin = fin;   // el archivo queda definido en su extensión y queda agregado al "disco"
    file1.close();

}

void eliminar_archivo( Dir*curs, string clav ,  Nodo<File>* lista){
    Line aux;
    File mf;
    mf.id = clav;
    Nodo<File>* f;
    Nodo<File>* p = lista;
    f = buscar<File>(mf , curs->archs , criterio_arch);
    int i;
    int in;
    int j;
    fstream file1;
    fstream file2;



    file2.open("disk2.bin", ios::binary | ios::in);
    while(p->sig){  // se buscan los archivos de la lista uno por uno
        if (p->dato.ini == f->dato.ini && p->dato.fin == f->dato.fin){ // si el archivo a eliminar es igual al de la lista lo pasa
            continue;
        }
        else{
            file1.open("disk.bin" , ios::binary | ios::out);
            j = 0;
            in = i;
            while(file1>>aux){
                if (j -1 > p->dato.ini && j -1 < p->dato.fin){  
                    //cout << aux.cont << endl;
                    file2 << aux; // se escribe el dato en el segundo archivo
                    i++;
                }
                j ++;
            }
            p->dato.ini = in;
            p->dato.fin = i;
            file1.close();
        }
    }
    
    remove("disk.bin");
    //rename("disk2.bin" , "disk.bin");
}





#endif