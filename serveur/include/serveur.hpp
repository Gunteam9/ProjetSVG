//
// Created by ionas on 11/02/2020.
//

#pragma once

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include <vector>
#include "../../vendor/exceptions/include/udpRuntimeException.hpp"
#include "../../vendor/exceptions/include/udpBindsException.hpp"
#include "../../vendor/exceptions/include/udpReceiveException.hpp"
#include "../../vendor/cbor11/cbor11.hpp"
#include "dataparser.hpp"
#include "../../vendor/exceptions/include/erreurException.hpp"


#define PORT 6789
#define IP_SERVER "127.0.0.2"
#define IP_CLIENT "127.0.0.3"


using namespace std;

class Serveur {

private:
    int sock;

public:
    Serveur();

    virtual ~Serveur();

    int getMaSocket() const;

    int getPort() const ;

    void startServer();

};


