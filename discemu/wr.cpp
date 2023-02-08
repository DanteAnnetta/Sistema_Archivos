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

ostream& seekp(streampos pos);
Line aux;
Line auxw;

int main(){
    int ini = 0;
    fstream file1;
    file1.open("disk.bin" , ios::binary | ios::in);  // se abre en modo lectura-escritura

    while(file1 >> aux){ // se recorre el archivo
        //cout << aux.cont << endl;
        ini++;
    }
    file1.close();
    file1.open("disk.bin" , ios::binary | ios::app);

    // se escribe una linea al final del archivo 


    cout << "/" ;
    cin.getline(lin , lline , '\n');
    for(int i = 0; i< lline ;i++){
        auxw.cont += lin[i];
    }

    file1 << auxw;

    // se reinicia el puntero
    file1.close();
    file1.open("disk.bin" , ios::binary | ios::in);

    
    while(file1 >> aux){ // se recorre el archivo
        cout << aux.cont << endl;
        //ini++;
    }


    file1.close();

    return 0;
    
}