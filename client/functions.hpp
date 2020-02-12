//
// Created by gunteam on 05/02/2020.
//

#pragma once

#include <string>
#include "../cbor11/cbor11.hpp"
#include <netinet/in.h>
#include <cstring>
#include "Exceptions/udpRuntimeException.h"
#include "Exceptions/udpSendingException.h"


class functions {
public:
    functions();
    virtual ~functions();

    int const PORT = 6789;

    void sendData(cbor args0);

private:

    int sckt;

};

