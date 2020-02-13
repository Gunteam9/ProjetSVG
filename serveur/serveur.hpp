//
// Created by ionas on 11/02/2020.
//

#pragma once

#include <string>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>

#include "../exceptions/erreurException.hpp"

#define PORT    6789
#define MAXLINE 1024

using namespace std;

class Serveur {

private:
    int server_fd;
    sockaddr_in address;


public:
    Serveur();

    virtual ~Serveur();

    int getMaSocket() const;

    int getPort() const ;

    void startServer();

};


