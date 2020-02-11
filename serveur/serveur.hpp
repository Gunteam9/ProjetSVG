//
// Created by ionas on 11/02/2020.
//

#pragma once

#include <string>
#include <netinet/in.h>
#include <iostream>

#include "../erreur/erreur.hpp"

#define PORT    6789
#define MAXLINE 1024

using namespace std;

class Serveur {

private:
    int maSocket;
    sockaddr_in adresseServer;
    sockaddr_in adresseClient;


public:
    Serveur(const sockaddr_in &adresseClient);

    virtual ~Serveur();

    int getMaSocket() const;

    int getPort() const ;

    void startServer();

};


