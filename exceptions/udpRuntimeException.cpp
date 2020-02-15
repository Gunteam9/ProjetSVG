#include "udpRuntimeException.hpp"
//
// Created by gunteam on 11/02/2020.
//


using namespace std;

udpRuntimeException::udpRuntimeException(const string addr, const int PORT) {

    cout << "Impossible de créer la socket pour " << addr <<  ":" << PORT << endl;
    exit(EXIT_FAILURE);
}
