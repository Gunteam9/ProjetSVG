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
#include "../../vendor/exceptions/udpRuntimeException.hpp"
#include "../../vendor/exceptions/udpBindsException.hpp"
#include "../../vendor/exceptions/udpReceiveException.hpp"
#include "../../vendor/cbor11/cbor11.hpp"
#include "dataparser.hpp"
#include "window.hpp"
#include "../../vendor/exceptions/errorException.hpp"


#define PORT 6789
#define IP_SERVER "127.0.0.2"
#define IP_CLIENT "127.0.0.3"


using namespace std;

class Serveur {

private:
    char* IMAGE_SVG ;
    int sock;

    void envoiDesAttributs(Window& w,sockaddr_in from) ;

public:
    Serveur(char* IMAGE_SVG);

    virtual ~Serveur();

    int getMaSocket() const;

    int getPort() const ;

    void startServer(Window&);


};


