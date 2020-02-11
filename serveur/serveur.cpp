//
// Created by ionas on 11/02/2020.
//

#include "serveur.hpp"


Serveur::Serveur(const sockaddr_in &adresseClient) : adresseClient(adresseClient) {
    // Creating socket file descriptor
    this->maSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); // ON CRée le SOCKET

    // ON OUVRE LE SOCKET
    adresseServer.sin_family    = AF_INET; // ADresse IPV4
    adresseServer.sin_addr.s_addr = INADDR_ANY; // Permet d'écouter sur toutes les interfaces locales
    adresseServer.sin_port = htons(PORT); //on traduit le port en endianess réseau

    int resBind = bind(this->maSocket, (const struct sockaddr *)&this->adresseServer, sizeof(this->adresseServer));
    if ( resBind < 0 )
    {
        throw Erreur("le binding a échoué");

    }

}


Serveur::~Serveur() {

}


void Serveur::startServer() {

    while (true) {


        socklen_t fromlen = sizeof(adresseClient);

        char buffer[MAXLINE]; // la capacité de lecture du buffer



        int res2 = recvfrom(this->maSocket, buffer, MAXLINE, MSG_WAITALL, reinterpret_cast<sockaddr *>(&adresseClient),&fromlen);

        if (res2 <= 0) {
            throw Erreur("Problème de reception de données");
        }
        cout<<"message recu " <<  buffer;
    }

}

int Serveur::getMaSocket() const {
    return maSocket;
}

int Serveur::getPort() const {
    return 6789;
}

