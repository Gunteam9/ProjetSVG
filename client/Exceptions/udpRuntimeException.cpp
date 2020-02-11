#include "udpRuntimeException.h"
//
// Created by gunteam on 11/02/2020.
//

#include <iostream>

using namespace std;

udpRuntimeException::udpRuntimeException(sockaddr_in addr, const int PORT) {

    cout << "Impossible de créer la socket pour " << addr.sin_addr.s_addr <<  ":" << PORT << endl;
}
