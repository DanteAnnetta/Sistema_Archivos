#include <iostream>
#include "arch.hpp"
using namespace std;

Dir home;
Dir *curs;
string com;
string cl;
bool loop = true;



int main(){
    home.id = "home";
    curs = &home;
    mkdir("home" , curs);
    cd("home" , curs);
    mkdir("dante", curs);
    cd("dante", curs);
    mkdir("desktop" , curs);
    mkdir("docs" , curs);
    mkdir("downloads" , curs);

// buscar una forma más eficiente de hacer la selección de comandos
    while(loop){
        cout << "/ ";
        cin >> com ;
        if (com == "ls"){
            ls(curs);
        }
        if (com == "mkdir"){
            cout << " ";
            cin >> cl;
            mkdir(cl , curs);
        }
        if(com == "cd"){
            cout << " ";
            cin >> cl;
            cd(cl , curs);
        }
        if (com == "exit"){
            //loop = false;
            break;
        }


    }

    return 0;
}
