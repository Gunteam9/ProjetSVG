//
// Created by ionas on 10/02/2020.
//




#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include "../exceptions/erreurException.hpp"

#define PORT     6789
#define MAXLINE 1024

using namespace std;

int main(int argc, char *argv[]) {

    int maSocket;

    sockaddr_in adresseServer;
    sockaddr_in adresseClient;

    // Creating socket file descriptor
    maSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); // ON CRée le SOCKET


    // ON OUVRE LE SOCKET
    adresseServer.sin_family    = AF_INET; // ADresse IPV4
    adresseServer.sin_addr.s_addr = INADDR_ANY; // Permet d'écouter sur toutes les interfaces locales
    adresseServer.sin_port = htons(PORT); //on traduit le port en endianess réseau

    // On bind la socket
    int res = bind(maSocket, (const struct sockaddr *)&adresseServer, sizeof(adresseServer));
    if ( res < 0 )
    {
        throw ErreurException("le binding a échoué");
    }

    while (true) {

        cout << "here" << endl;

        socklen_t fromlen = sizeof(adresseClient);

        char buffer[MAXLINE]; // la capacité de lecture du buffer



        int res2 = recvfrom(maSocket, buffer, MAXLINE, MSG_WAITALL, reinterpret_cast<sockaddr *>(&adresseClient),&fromlen);

        cout << "here2" << endl;

        if (res2 <= 0) {
            throw ErreurException("Problème de reception de données");
        }
        cout<<"message recu " <<  buffer; // le code marche pour un string, à moi de le changer en message cbor


    }


    return 0;
}


