#ifndef ARCH_HPP_INCLUDED
#define ARCH_HPP_INCLUDED

#include <iostream>
#include "listascomp.hpp"
#include "listasordc.hpp"
#include "rwstring.hpp"

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
    int q = 0;
    //while (dat!=":q"){ 
    while (q < 10){   // este método no funciona
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
        q++;
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

//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------









#endif 
