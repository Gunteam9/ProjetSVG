//
// Created by gunteam on 05/02/2020.
//

#pragma once

#include <string>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include "../../cbor11/cbor11.hpp"
#include "../../exceptions/include/udpRuntimeException.hpp"
#include "../../exceptions/include/udpSendingException.hpp"
#include "../../exceptions/include/udpBindsException.hpp"
#include "../../exceptions/include/udpAdresseConvertionException.hpp"
#include "../../exceptions/include/udpConnectionException.hpp"

#define PORT 6789
#define IP_SERVER "127.0.0.2"
#define IP_CLIENT "127.0.0.3"


class functions {
public:
    functions();
    virtual ~functions();

    void sendData(cbor::map data);

    cbor::binary entry();

private:

    //Socket
    int sock = 0;

    //Addresse du serveur
    struct sockaddr_in serv_addr;

};