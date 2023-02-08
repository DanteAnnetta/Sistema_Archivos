// el objetivo de este programa es el de crear un gestor de archivos binarios capaz de almacenar los datos
// en primer lugar el objetivo es almacenar arreglos de caracteres correspondientes a las lineas de los archivos

// para poder lograr la asignación correcta de archivos-contenido, es necesario indicarle en que linea se guarda cada uno y es ahí donde entra este programa



#include<iostream>
#include<fstream>
#include "rwstring.hpp"
using namespace std;

const int lline = 180;
char lin[lline];

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





int main(){
    Line aux;
    fstream file1;
    
    // modo lectura

    // modo escritura
    file1.open("disk.bin" , ios::binary | ios::out );
    if(!file1){
        cout << "Error: no se pudo abrir el archivo" << endl;
    }

    for (int i = 0 ; i < 10 ; i++){
        cout << "/" ;
        cin.getline(lin , lline , '\n');
        for(int i = 0; i< lline ;i++){
            aux.cont += lin[i];
        }

        file1 << aux;
        aux.cont = "";
    }
    
    file1.close();
    return 0;
}