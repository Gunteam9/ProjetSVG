//
// Created by gunteam on 05/02/2020.
//

#ifndef CORBEAU_NEONAKIS_TOULARHMINE_TRIMOULET_FUNCTIONS_H
#define CORBEAU_NEONAKIS_TOULARHMINE_TRIMOULET_FUNCTIONS_H


#include <string>
#include "../cbor11/cbor11.hpp"

class functions {
public:
    functions();
    virtual ~functions();

    int const PORT = 6789;

    void sendData(cbor args0);

private:

    int sckt;

};


#endif //CORBEAU_NEONAKIS_TOULARHMINE_TRIMOULET_FUNCTIONS_H
