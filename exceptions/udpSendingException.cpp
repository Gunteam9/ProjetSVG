//
// Created by gunteam on 11/02/2020.
//

#include "include/udpSendingException.hpp"

#include <iostream>

using namespace std;

udpSendingException::udpSendingException() {
    cout << "Erreur dans l'envoie des données" << endl;
    exit(EXIT_FAILURE);
}


udpSendingException::udpSendingException(const char *w) {
    cout << w << endl;
    exit(EXIT_FAILURE);
}

