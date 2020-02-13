//
// Created by gunteam on 13/02/2020.
//

// Source: https://www.geeksforgeeks.org/socket-programming-cc/
// Source: https://stackoverflow.com/questions/31955514/simple-udp-socket-code-sending-and-receiving-messages

// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "../cbor11/cbor11.hpp"
#include "../exceptions/udpRuntimeException.h"
#include "../exceptions/udpAdresseConvertionException.h"
#include "../exceptions/udpBindsException.h";
#include "../exceptions/udpConnectionException.h"
#include "../exceptions/udpSendingException.h"

#define PORT 6789
#define IP_CLIENT "127.0.0.2"
#define IP_SERVEUR "127.0.0.3"

using namespace std;

int main(int argc, char const *argv[])
{
    //Socket
    int sock = 0;

    //Addresse du serveur
    struct sockaddr_in serv_addr;

    //Message
    char *hello = "Hello from client";

    //Buffer
    char buffer[1024] = {0};

    //Création de la socket
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        throw udpRuntimeException(IP_CLIENT, PORT);
    }
    cout << "Socket créée" << endl;

    //Initilisation de la socket
    serv_addr.sin_addr.s_addr = inet_addr(IP_CLIENT);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);


    // Convertion des addresses IP en binaire
    if(inet_pton(AF_INET, IP_CLIENT, &serv_addr.sin_addr) <= 0)
    {
        throw udpAdresseConvertionException();
    }
    cout << "Convertion effectuée" << endl;

    // Binds
    if (bind(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        throw udpBindsException();
    }
    cout << "Bind effectué" << endl;

    // Modification de l'ip pour atteindre le serveur
    serv_addr.sin_addr.s_addr = inet_addr(IP_SERVEUR);

    // Connexion au serveur
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        throw  udpConnectionException(IP_SERVEUR, PORT);
    }
    cout << "Connexion effectué" << endl;

    // Envoie de message
    if(send(sock, hello, strlen(hello), 0) < 0) {
        throw udpSendingException();
    }
    cout << "Message envoyé" << endl;

    return 0;
}
