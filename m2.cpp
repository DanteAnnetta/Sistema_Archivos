#include <iostream>
#include "arch.hpp"
using namespace std;

Dir home;
Dir *curs;
Nodo<File>* listafs;
string com;
string cl;
string path = "/home";
bool loop = true;



int main(){
    home.id = "home";
    curs = &home;
    mkdir("dante", curs);
    cd("dante", curs , path);
    mkdir("desktop" , curs);
    mkdir("docs" , curs);
    mkdir("downloads" , curs);

// buscar una forma más eficiente de hacer la selección de comandos
    while(loop){
        //cout << path << "@ ";  // hasta corregir el bug de la ruta absoluta se usa esto
        cout << curs->anterior->id<< "/" << curs->id << "@ ";
        cin >> com ;
        if (com == "ls"){
            ls(curs);
        }
        if (com == "mkdir"){
            //cout << " ";
            cin >> cl;
            mkdir(cl , curs);
        }
        if (com == "mkfile"){
            //cout << " ";
            cin >> cl;
            mkfile(cl , curs ,  listafs);
        }
        if (com == "rmdir"){
            //cout << " ";
            cin >> cl;
            rmdir(cl , curs);
        }
        if (com == "rmfile"){
            //cout << " ";
            cin >> cl;
            rmfile(cl , curs ,  listafs);
        }
        if(com == "cd"){
            //cout << " ";
            cin >> cl;
            cd(cl , curs, path);
        }
        if(com == "cat"){
            //cout << " ";
            cin >> cl;
            mostrar_archivo(curs , cl , listafs);
        }
        
        if(com == "cls"){ // en teoría esto solo debería funcionar en linux (hacer genérico a cualquier sistema)
            system("clear");
        }
        
        if (com == "exit"){
            break;
        }


    }

    return 0;
}
