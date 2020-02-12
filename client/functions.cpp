//
// Created by gunteam on 05/02/2020.
// Source: https://bousk.developpez.com/cours/reseau-c++/UDP/01-introduction-premiers-pas/ - https://bousk.developpez.com/cours/reseau-c++/TCP/04-serveur-premiers-pas
//

// Pourquoi utiliser htons: https://stackoverflow.com/questions/19207745/htons-function-in-socket-programing
//

#include "functions.hpp"

using namespace std;

functions::functions() {

    /*
     * Création de la socket
     *
     */
     sckt = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);


    /*
     * Ouverture de la socket
     *
     */
    sockaddr_in addr;

    // Permet d'écouter sur toutes les interfaces locales
    addr.sin_addr.s_addr = INADDR_ANY;

    // Traduction du port en htons port
    addr.sin_port = htons(PORT);

    // Pour IPV4
    addr.sin_family = AF_INET;

    // Binding
    int res = bind(sckt, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));

    //En cas d'erreur
    if (res != 0)
        throw udpRuntimeException(addr, PORT);



}

functions::~functions() {

}

void functions::sendData(cbor arg0) {

    cout << sizeof(arg0) << endl;

    sockaddr_in dst;

    /***************************
     *
     *
     *  METTRE L'IP A LA PLACE DE "ADDRESSE"
     *  Et décommenter la ligne
     *
     *
     ***************************/

    //dst.sin_addr = ADRESSE;
    dst.sin_port = PORT;
    dst.sin_family = AF_INET;
    int myId = 5000000;
    memcpy(&arg0, reinterpret_cast<const void *>(myId), sizeof(myId));
    int ret = sendto(sckt, reinterpret_cast<const void *>(myId), 500000, 0, reinterpret_cast<const sockaddr*>(&dst), sizeof(dst));

    //Erreur lors de l'envoi
    if (ret < 0)
        throw udpSendingException();
}

