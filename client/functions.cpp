//
// Created by gunteam on 05/02/2020.
// Source: https://bousk.developpez.com/cours/reseau-c++/UDP/01-introduction-premiers-pas/ - https://bousk.developpez.com/cours/reseau-c++/TCP/04-serveur-premiers-pas
//
#include "include/functions.hpp"


using namespace std;

functions::functions() {

    //////////////////////////////////////////////
    //                                          //
    //                                          //
    //                  SOCKET                  //
    //                                          //
    //                                          //
    //////////////////////////////////////////////



    //Création de la socket
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        throw udpRuntimeException(IP_CLIENT, PORT);
    }

    //Initilisation de la socket
    serv_addr.sin_addr.s_addr = inet_addr(IP_CLIENT);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);


    // Convertion des addresses IP en binaire
    if(inet_pton(AF_INET, IP_CLIENT, &serv_addr.sin_addr) <= 0)
    {
        throw udpAdresseConvertionException();
    }

    // Binds
    if (bind(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        throw udpBindsException();
    }

    // Modification de l'ip pour atteindre le serveur
    serv_addr.sin_addr.s_addr = inet_addr(IP_SERVER);


    //////////////////////////////////////////////
    //                                          //
    //                                          //
    //     Récupérations des informations       //
    //                                          //
    //                                          //
    //////////////////////////////////////////////


    sendData(cbor::map {{"?", "?"}});

    getModifiableInformations();

}

functions::~functions() {

}

void functions::sendData(cbor::map data) {

    cbor::binary encoded = cbor::encode(data);
    std::vector<unsigned char> v = encoded;

    std::vector<unsigned char>::iterator it;

    char* total = new char[v.size()];
    int i=0;
    for(it = v.begin(); it < v.end() ; ++it){
        total[i]=(*it);
        i++;
    }


    // Envoie de message
    if (sendto(sock, total, strlen(total), 0, (const sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
        throw udpSendingException();
    }
    cout << "Message envoyé" << endl;

}

void functions::getModifiableInformations() {
    std::cout << "En attente de la réception des données modifiables" << std::endl;
    while (true) {
        char buffer[1024] = {0};

        if (recv(sock, buffer, sizeof(buffer), 0) < 0) {
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

    }

}

void functions::showModifiableItems(cbor::binary data){
    cbor::map ModifiableItems = cbor::decode(data);
    string choice;
    for(auto it = ModifiableItems.begin(); it != ModifiableItems.end(); ++it){
        cout << "Souhaitez-vous faire cette modification? (y: yes, n: no)" << endl;
        cout << (string) it->first << ": " << (string) it->second << endl;
        cin >> choice;
        if(choice.compare("y")==0){
            //insert function
            break;
        }
    }
}

cbor::binary functions::entry(){
    double sun_x;
    double sun_y;
    /*
    cout << "Entrez la position du soleil sur l'axe X" << endl;
    cin >> sun_x;
    cout << "Entrez la position du soleil sur l'axe Y" << endl;
    cin >> sun_y;
     */



    cbor::map message = {
            { "sun_x", sun_x },
            { "sun_y", sun_y }
    };
    
    return cbor::encode(message);
}