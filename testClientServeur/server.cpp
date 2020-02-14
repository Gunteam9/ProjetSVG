//
// Created by gunteam on 13/02/2020.
//

// Source: https://www.geeksforgeeks.org/socket-programming-cc/
// Source: https://stackoverflow.com/questions/31955514/simple-udp-socket-code-sending-and-receiving-messages

// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include "../exceptions/udpRuntimeException.h"
#include "../exceptions/udpBindsException.h";
#include "../exceptions/udpReceiveException.h"

#define PORT 6789
#define IP_CLIENT "127.0.0.2"
#define IP_SERVEUR "127.0.0.3"

using namespace std;

int main(int argc, char const *argv[])
{
    //Socket
    int sock;

    //Addresse IP
    struct sockaddr_in address;

    //Buffer
    char buffer[1024] = {0};

    // Création de la socket
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        throw udpRuntimeException(IP_SERVEUR, PORT);
    }
    cout << "Socket créée" << endl;

    // Initialisation de la socket
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(IP_SERVEUR);
    address.sin_port = htons(PORT);

    // Binding
    if (bind(sock, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        throw udpBindsException();
    }
    cout << "Conversion de l'IP effectuée" << endl;

    // Récupération de données
    while (true) {

        if(recv(sock, buffer, sizeof(buffer), 0) < 0) {
            throw udpReceiveException();
        }
        puts(buffer);

    }

    return 0;
}
