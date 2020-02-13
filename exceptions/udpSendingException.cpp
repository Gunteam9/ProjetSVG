//
// Created by gunteam on 11/02/2020.
//

#include "udpSendingException.h"

#include <iostream>

using namespace std;

udpSendingException::udpSendingException() {
    cout << "Erreur dans l'envoie des données" << endl;
}


udpSendingException::udpSendingException(const char *w) {
    cout << w << endl;
}

