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
    int iter = 0;
    //Nodo<Dir>* aux = nullptr; // puntero para poder realizar recorridos en arboles
    //Nodo<File> * archs = nullptr;
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


void mkdir(string clav , Dir* curs){
    Dir mk;
    Nodo<Dir> * ck; // esto se encarga de chequear que una carpeta es única
    mk.id = clav;
    mk.anterior = curs;
    //agregar<Dir>(curs->sigs, mk);
    ck = buscar<Dir>( mk , curs->sigs , criterio_carpeta);
    if(ck == nullptr){
        insertar<Dir>(mk , curs->sigs , criterio_carpeta);
        /* // descomentar esto si se vuelven a usar los nodos auxiliares
        if(curs->aux == nullptr){
            Nodo<Dir>* ind = new Nodo<Dir>;
            ind->dato = mk;
            curs->aux = ind;  // si es la primer carpeta que se crea, entonces aux es igual al nodo de la misma
        }
        */
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
            if (curs->sigs == nullptr){ // si se elimina la ultima carpeta, se vacia el puntero auxiliar
                //curs->aux = nullptr;
            }
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




void recorrer_arbol(Dir* root ){

    int count = 0;
    bool proxicorta = false;
    while(true){ 
        cout << root->id << endl;
        if(obtener_siguiente(root->iter , root->sigs)){
            cout << "Adelante" << endl << endl;
            root = &obtener_siguiente(root->iter , root->sigs)->dato;
            root->anterior->iter ++;

        }
        else{
            cout << "Atras" << endl << endl;
            root = root->anterior;

        }


        // de momento esto funciona bien
        if (proxicorta){
            break;
        } 

        if(es_ultimo(root)){ 
                proxicorta = true;
                //break;
        }
        
        count ++;
    }
    cout << endl << count << endl;

}




/*

void recorrer_arbol(Dir* root ){
    Dir* ant = root->anterior; // puntero auxiliar para registrar la ultima iteracion
    //bool paso = false;
    while(true){
        cout << root->id << endl;

        if(root->sigs != nullptr ){// si hay carpetas por debajo que esta para recorrer

            if (ant == root->anterior){  // si se esta iterando de arriba hacia abajo (caso 1)
                cout << "   --caso1" << endl;
                ant = root;
                //root->iter ++;
                root = &obtener_siguiente(root->iter, root->sigs)->dato;
                root->anterior->iter ++;                
                
            }

            else{ // si se itera de abajo hacia arriba (caso 2)
                cout << "   --caso2" << endl;
                ant = root;
                root = root->anterior;
                if(root->sigs->sig !=nullptr){// si la carpeta tiene mas de una subcarpeta   (caso contrario se llama al caso 3)
                    ant = root->anterior; // se adapta para que sea una instancia del caso anterior
                }
                //paso = true; // verifica un salto de caso 2 a caso 1
            }

        }
        
        else{// cuando se encuentra con una carpeta terminal (caso 3) (se itera de abajo hacia arriba si o si)

            if(es_ultimo(root)){
                break;
            }   
            cout << "   --caso3" << endl; // dependiendo de como es la carpeta de arriba, hace un caso 1 o un caso 2
            

            if(root->anterior->sigs->sig){  // salto a un caso 1
                root = root->anterior;
                ant = root->anterior;
            }
            else{   // salto a un caso 2
                ant = root;
                root = root->anterior;
            }


        }
    }   
    
}


*/


#endif 
