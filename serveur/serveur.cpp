//
// Created by ionas on 11/02/2020.
//

#include "serveur.hpp"
#include "../cbor11/cbor11.hpp"

using namespace std;

Serveur::Serveur(){
    int opt = 1;
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

}


Serveur::~Serveur() {

}


void Serveur::startServer() {
    int new_socket;

    int addrlen = sizeof(address);

    char buffer[1024] = {0};

    cbor buffer2[1024] = {0};


    int valread;

    while(true) {
        if (listen(server_fd, 3) < 0) {
            perror("listen");
            exit(EXIT_FAILURE);
        }
        if ((new_socket = accept(server_fd, (struct sockaddr *) &address,
                                 (socklen_t *) &addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        valread = read(new_socket, buffer, 1024);
        //cbor rec=buffer;
        cout << "recu : " << buffer;

    }


}

int Serveur::getMaSocket() const {
    return this->server_fd;
}

int Serveur::getPort() const {
    return 6789;
}

