//
// Created by gunteam on 13/02/2020.
//

#include "include/udpBindsException.hpp"

using namespace std;

udpBindsException::udpBindsException() {

    cout << "Binding impossible" << endl;
    exit(EXIT_FAILURE);

}
