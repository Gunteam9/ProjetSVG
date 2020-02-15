//
// Created by gunteam on 13/02/2020.
//

#include "include/udpReceiveException.hpp"

using namespace std;

udpReceiveException::udpReceiveException() {

    cout << "Impossible de recevoir le message" << endl;
    exit(EXIT_FAILURE);

}
