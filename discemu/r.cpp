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
    file1.open("disk.bin" , ios::binary | ios::in);

    if(!file1){
        cout << "Error: no se pudo abrir el archivo" << endl;
    }
    int ini = 0;
    int fin = 10;
    int i = 0;
    while(file1 >> aux){
        if (i  > ini -1 && i < fin){     // de esta forma se pueden leer lineas especificas de un archivo
            cout << aux.cont << endl;
        }
        i ++;
    }
    file1.close();
    cout << "Listo" << endl;
    return 0;
}