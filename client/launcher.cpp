//
// Created by Romain on 11/02/2020.
//

#include "include/functions.hpp"

using namespace std;

int main() {

    //Instancie la classe principal du client
    functions func;

    //La map à envoyer au serveur pour récupérer les infos
    cbor::map data = {
            { "?", "?"},
    };

    func.sendData(data);

    return 0;
}