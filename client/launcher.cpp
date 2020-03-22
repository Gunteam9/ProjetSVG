//
// Created by Romain on 11/02/2020.
//

#include "include/consoleClient.hpp"
#include "test_gtk/client_graphique.hpp"

using namespace std;

int main(int argc, char* argv[]) {

    //Instancie la classe principal du client
    ClientGraphique c(&argc, &argv);

    c.start();
    return 0;
}