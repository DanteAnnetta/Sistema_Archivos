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

struct Dir{  // la id de una carpeta podría ser su nivel concatenado con su nombre
    string id;
    Dir * anterior = nullptr;
    Nodo<Dir> * sigs = nullptr;
    int iter = 0;
    int nivel = 0; // indicador de nivel, para poder reconstruir el arbol (persistencia)
};

struct Regdir{  // estructura que se utilizará para la persistencia del arbol
    string id;
    string anterior;
    int nivel;
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

ostream& operator << (ostream &os , Regdir r){
    os << " " << r.id << "  " << r.nivel << "   " << r.anterior;
    return os;
}

int criterio_carpeta(Dir a , Dir b){
    return a.id.compare(b.id);
}

int criterio_arch(File a , File b){
    return a.id.compare(b.id);
}

// probar como funciona
int criterio_nivel(Regdir a , Regdir b){
    if (a.nivel < b.nivel){
        return -1;
    }
    else{
        if (a.nivel == b.nivel){
            return 0;
        }
        else{
            return 1;
        }
    }
}


// función de conversión de datos para la persistencia
void operator >> (Dir d , Regdir& r){
    if(!d.anterior){
        r.anterior = "";
    }
    else{
        r.anterior = d.anterior->id;
    }
    r.id = d.id;
    r.nivel = d.nivel;
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


void mkdir(string clav , Dir* curs , Nodo<Regdir>* &listac){
    Dir mk;
    Regdir r;
    Nodo<Dir> * ck; // esto se encarga de chequear que una carpeta es única
    mk.id = clav;
    mk.anterior = curs;
    mk.nivel = curs->nivel + 1;
    ck = buscar<Dir>( mk , curs->sigs , criterio_carpeta);
    //cout << "Creando " << clav << endl;
    if(ck == nullptr){
        insertar<Dir>(mk , curs->sigs , criterio_carpeta);
        mk >> r;
        if(listac){ // cuando se carga el arbol (persistencia) los datos ya estan en la lista, no hay que editarlos
            insertar<Regdir>(r , listac , criterio_nivel);
        }
    }
    else{
        cout << "error: esa carpeta ya existe" << endl;
    }

}

void rmdir(string clav , Dir* curs, Nodo<Regdir>* listac){
    Dir mk;
    Regdir r;
    Nodo<Dir> * ck;
    mk.id = clav;
    ck = buscar<Dir>(mk , curs->sigs , criterio_carpeta);
    if (!ck){
        cout << "error: no se encontro la carpeta" << endl;
    }
    else{
        if(mk.sigs != nullptr){
            borrar<Dir>(mk , curs->sigs , criterio_carpeta);
            mk >> r;
            borrar<Regdir>(r , listac , criterio_nivel);
        }
        else{
            cout << "error: esta carpeta contiene otras carpetas adentro" << endl; // crear una forma recursiva de eliminarlas todas
        }
    }
}






void ls( Dir* curs){
    mostrar<Dir>(curs->sigs);
    cout << endl;
    //mostrar<File>(curs->archs);
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



template <typename T > Nodo<T>* obtener_siguiente(int dato , Nodo<T>* lista){
    int index = 0;
    while(index < dato){
        index++;
        lista = lista->sig;
        if(!lista){ // si lista es nullptr devuelve esto 
            break;
        }
    }
    return lista;
}

template<typename T> int obtener_cantidad(Nodo<T>* lista){
    int count = 0;
    while(lista){
        lista = lista->sig;
        count ++;
    }
    return count;
}

bool es_ultimo(Dir* rama){
    bool resul = true;
    while(rama){
        if(rama->iter < obtener_cantidad<Dir>(rama->sigs)){
            resul = false;
            break;
        }
        rama = rama->anterior;
    }
    return resul;
}



void restaurar_arbol(Dir* root ){ // esta función permite poder recorrer el arbol indefinidamente
    bool proxicorta = false;
    while(true){ 
        //cout << root->id << endl;
        
        if(obtener_siguiente(obtener_cantidad<Dir>(root->sigs)  -  root->iter , root->sigs)){
            //cout << "Adelante" << endl << endl;
            root = &obtener_siguiente(obtener_cantidad<Dir>(root->sigs)  -  root->iter , root->sigs)->dato;
            root->anterior->iter --;

        }
        else{
            //cout << "Atras" << endl << endl;
            root = root->anterior;

        }

        if (proxicorta){
            break;
        } 

        if(root->iter == 0 && !root->anterior){
                proxicorta = true;
        }
        
    }
}



void recorrer_arbol(Dir* root ){ 

    bool proxicorta = false;
    while(true){ 
        cout << root->id << endl;
        if(obtener_siguiente(root->iter , root->sigs)){
            //cout << "Adelante" << endl << endl;
            root = &obtener_siguiente(root->iter , root->sigs)->dato;
            root->anterior->iter ++;

        }
        else{
            //cout << "Atras" << endl << endl;
            root = root->anterior;

        }

        if (proxicorta){
            break;
        } 

        if(es_ultimo(root)){ 
                proxicorta = true;
        }
        
    }
     restaurar_arbol(root);
}







// funcion que recorre toda la lista de carpetas y agrega las correspondientes a este directorio
void rya_lista(Dir* &root , Nodo<Regdir>* listac ){
    Nodo<Regdir>* load = nullptr; // puntero auxiliar para cuando se carga el arbol
    Nodo<Regdir>* aux = listac;
    while(aux){
        if(aux->dato.anterior == root->id && aux->dato.nivel == root->nivel + 1){
            mkdir(aux->dato.id , root , load);
        }
        aux = aux->sig;
    }

}


// void recorrer_load() // función que por cada iteración del arbol ejecuta rya_lista (estructura de recorrer_arbol)



void recorrer_load(Dir* &root , Nodo<Regdir>* listac ){ 

    bool proxicorta = false;
    while(true){ 
        //cout << root->id << endl;
        rya_lista(root , listac);
        if(obtener_siguiente(root->iter , root->sigs)){
            //cout << "Adelante" << endl << endl;
            root = &obtener_siguiente(root->iter , root->sigs)->dato;
            root->anterior->iter ++;

        }
        else{
            //cout << "Atras" << endl << endl;
            root = root->anterior;

        }

        if (proxicorta){
            break;
        } 

        if(es_ultimo(root)){ 
                proxicorta = true;
        }
        
    }
     restaurar_arbol(root);
}






#endif 
