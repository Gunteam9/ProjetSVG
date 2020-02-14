//
// Created by gunteam on 13/02/2020.
//

#include "udpBindsException.h"

using namespace std;

udpBindsException::udpBindsException() {

    cout << "Binding impossible" << endl;
    exit(EXIT_FAILURE);

}
