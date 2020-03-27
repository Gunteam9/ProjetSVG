//
// Created by Romain on 11/02/2020.
//

#include "include/client_console.hpp"
#include "include/client_graphique.hpp"

using namespace std;

int main(int argc, char* argv[]) {

    if(argc == 1){
        cout << "Veuillez préciser 0 pour une interface console, 1 pour une interface graphique" << endl;
    }else{
        bool b = std::stoi(std::string(argv[1]));
        if(b){
            //Instancie la classe principal du client
            ClientGraphique(&argc, &argv).start();
        }else{
            ClientConsole().start();
        }
    }

    return 0;
}