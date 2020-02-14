//
// Created by gunteam on 13/02/2020.
//

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include <vector>
#include "../exceptions/udpRuntimeException.h"
#include "../exceptions/udpBindsException.h"
#include "../exceptions/udpReceiveException.h"
#include "../cbor11/cbor11.hpp"
#include "../serveur/dataparser.hpp"

#define PORT 6789
#define IP_SERVEUR "127.0.0.3"

using namespace std;

int main(int argc, char const *argv[])
{
    //Socket
    int sock;

    //Addresse IP
    struct sockaddr_in address;


    // Création de la socket
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        throw udpRuntimeException(IP_SERVEUR, PORT);
    }

    // Initialisation de la socket
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(IP_SERVEUR);
    address.sin_port = htons(PORT);

    // Binding
    if (bind(sock, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        throw udpBindsException();
    }


    // Récupération de données
    while (true) {
        char buffer[1024] = {0};

        if(recv(sock, buffer, sizeof(buffer), 0) < 0) {
            throw udpReceiveException();
        }

        std::vector<unsigned char> encoded ;

        encoded.reserve(strlen(buffer));

        for(int i=0 ; i < strlen(buffer) ; ++i){
            encoded.push_back(buffer[i]);
        }


        cbor::binary encded = encoded;

        DataParser p ;
        std::vector<Message> vT =p.lireMessage(encded);

        std::cout << vT[0] << endl;

        //puts(buffer);

    }

    return 0;
}
