//
// Created by gunteam on 05/02/2020.
//

#pragma once


#include <string>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include "../../vendor/cbor11/cbor11.hpp"
#include "../../vendor/exceptions/include/udpRuntimeException.hpp"
#include "../../vendor/exceptions/include/udpSendingException.hpp"


class functions {
public:
    functions();
    virtual ~functions();

    int const PORT = 6789;

    void sendData(cbor::binary data);

    cbor::binary entry();

private:

    int sckt;

};