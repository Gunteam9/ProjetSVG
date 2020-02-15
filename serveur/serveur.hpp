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
#include "../exceptions/udpRuntimeException.hpp"
#include "../exceptions/udpBindsException.hpp"
#include "../exceptions/udpReceiveException.hpp"
#include "../cbor11/cbor11.hpp"
#include "../serveur/dataparser.hpp"
#include "../exceptions/erreurException.hpp"


#define PORT 6789
#define IP_CLIENT "127.0.0.2"
#define IP_SERVEUR "127.0.0.3"


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


