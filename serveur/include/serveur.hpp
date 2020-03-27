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


using namespace std;

/**
 * Classe s'occupant du serveur en UDP sur le port 6789 avec son ip en 127.0.0.2
 */
class Serveur {

private:
    char* IMAGE_SVG ;
    int sock;

    /**
     * @brief Méthode qui envooie les attributs au client dès que le client envoie des '?' au serveur
     * @param w
     * @param from
     */
    void envoiDesAttributs(Window& w,sockaddr_in from) ;

public:
    /**
     * @brief Constructeur qui crée le serveur avec l'image svg en paramètres
     * @param IMAGE_SVG
     */
    Serveur(char* IMAGE_SVG);

    virtual ~Serveur();

    /**
     * Méthode qui initialise le serveur
     */
    void startServer(Window&);

    /**
     * @brief Méthode qui envoie les éléments de type style de l'image au client
     * @param in est l'adresse du client
     */
    void envoiDuCss(sockaddr_in in);
};


