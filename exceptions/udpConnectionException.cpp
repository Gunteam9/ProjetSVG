//
// Created by gunteam on 13/02/2020.
//

#include "udpConnectionException.hpp"

using namespace std;

udpConnectionException::udpConnectionException(const string addr, const int port) {

    cout << "Connexion au serveur" << addr << ":" << port << "impossible" << endl;
    exit(EXIT_FAILURE);
}
