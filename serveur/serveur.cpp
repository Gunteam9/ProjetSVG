//
// Created by ionas on 11/02/2020.
//

#include "include/serveur.hpp"

#include "include/window.hpp"

using namespace std;

Serveur::Serveur(){
    //Socket


    //Addresse IP
    struct sockaddr_in address;


    // Création de la socket
    if ((this->sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        throw udpRuntimeException(IP_SERVER, PORT);
    }

    // Initialisation de la socket
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(IP_SERVER);
    address.sin_port = htons(PORT);

    // Binding
    if (bind(sock, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        throw udpBindsException();
    }

}


Serveur::~Serveur() {

}


void Serveur::startServer() {
    std::cout << "le serveur a été lancé" << std::endl;
    while (true) {
        char buffer[1024] = {0};

        sockaddr_in from;
        socklen_t fromlen= sizeof(from);


        if (recvfrom(sock, buffer, sizeof(buffer), 0, reinterpret_cast<sockaddr*>(&from), &fromlen) < 0) {
            throw udpReceiveException();
        }


        std::vector<unsigned char> encodedMessge;

        int taille = strlen(buffer);

        //on reserve la place dans le vector,
        encodedMessge.reserve(taille);


        // on assigne les valeurs du buffer dans le vector
        for (int i = 0; i < taille; ++i) {
            encodedMessge.push_back(buffer[i]);
        }


        cbor::binary binaryEncodedMessage = encodedMessge;

        DataParser p;
        //ici on affiche les messages
        //il faudrait les envoyer a une methode de la window pour effectuer les changements
        std::vector<Message> vT = p.lireMessage(binaryEncodedMessage);

        std::cout << vT[0] << endl;

        Window::update(vT, constantes::MAISON_SVG);

    }

}

int Serveur::getMaSocket() const{
    return this->sock;
}



