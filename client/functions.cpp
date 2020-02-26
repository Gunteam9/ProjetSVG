//
// Created by gunteam on 05/02/2020.
// Source: https://bousk.developpez.com/cours/reseau-c++/UDP/01-introduction-premiers-pas/ - https://bousk.developpez.com/cours/reseau-c++/TCP/04-serveur-premiers-pas
//
#include "include/functions.hpp"

using namespace std;

functions::functions() {

    //Buffer

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

    // Connexion au serveur
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        throw  udpConnectionException(IP_SERVER, PORT);
    }

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
    if(send(sock, total, strlen(total), 0) < 0) {
        throw udpSendingException();
    }
    cout << "Message envoyé" << endl;

}

//
// Edit by Anael
//
// Entrées des modifications
// 

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
