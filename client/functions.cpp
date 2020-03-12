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


}

functions::~functions() {

}

void functions::sendData(cbor::map data) {

    for (auto it = data.begin(); it != data.end(); ++it) {
        cout << (string) it->first << " " << (string) it->second << endl;
    }

    cbor::binary encoded = cbor::encode(data);

    // Envoie de message
    if (sendto(sock, encoded.data(), encoded.size(), 0, (const sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
        throw udpSendingException();
    }
    cout << "Message envoyé" << endl;

    // Réception des informations modifiables
    if (data.begin()->first == "?")
        getModifiableInformations();
}

void functions::getModifiableInformations() {

    char buffer[1024] = {0};

    if (recv(sock, buffer, sizeof(buffer), 0) < 0) {
        throw udpReceiveException("Impossible de recevoir les éléments driven");
    }

    string element = (string) buffer;
    string delimiter = "\n";
    vector<string> modifiableItems;

    while (element.length() != 0) {
        modifiableItems.push_back(element.substr(0, element.find_first_of(delimiter)));
        element.erase(0, (int) element.find_first_of(delimiter)+1);
    }

    char buffer2[1024] = {0};

    if (recv(sock, buffer2, sizeof(buffer2), 0) < 0) {
        throw udpReceiveException("Impossible de recevoir les éléments de style");
    }

    element = (string) buffer2;

    string firstDelimiter = ": ";
    string secondDelimiter = " ";
    string mainDelimiter = "\n";

    vector<string> vectorStyleItems;
    map<string, vector<string> > styleItems;

    element.erase(0, element.find_first_of(mainDelimiter) + 1);

    while(element.length() != 0) {
        string key = element.substr(0, element.find_first_of(firstDelimiter));
        element.erase(0, element.find_first_of(firstDelimiter) + 2);
        string value = element.substr(0, element.find_first_of(mainDelimiter));
        element.erase(0, element.find_first_of(mainDelimiter) + 1);

        while(value.length() != 0) {
            vectorStyleItems.push_back(value.substr(0, value.find_first_of(secondDelimiter)));
            value.erase(0, (int) value.find_first_of(secondDelimiter) + 1);
        }

        styleItems.insert({key, vectorStyleItems});
        element.erase(0, (int) element.find_first_of(mainDelimiter) + 1);
    }

    this->styleItems = styleItems;

    showModifiableItems(modifiableItems);

}



void functions::showModifiableItems(vector<string> modifiableItems) {

    //Affichage des éléments modifiables
    for (auto it = modifiableItems.begin(); it != modifiableItems.end(); ++it) {
        cout << (*it) << endl;
    }


    string choice;
    do {
        cout << "Entrez le nom de l'item a modifier" << endl;
        getline(cin, choice);
    } while (!isItemExist(modifiableItems, choice));


    for(vector<string>::iterator it = modifiableItems.begin(); it != modifiableItems.end(); ++it) {
        if(choice.compare((*it))==0){
            data.insert({choice, modifyItem(choice)});
            break;
        }
    }


    bool resp = this->yesNoQuestion("Voulez vous modifier d'autres item ? (yes / no)");
    if (resp)
        showModifiableItems(modifiableItems);
    else
        sendData(data);


}


string functions::modifyItem(string item){
    string newValue;
    bool resp = true;

    //Si l'item se termine par _style
    if (item.find_last_of("_style") == item.length() - 1) {
        while (resp) {
            cout << "Liste des éléments CSS modifiables: " << endl;

            for (map<string, vector<string> >::iterator it = this->styleItems.begin(); it != this->styleItems.end(); ++it) {
                if (it->first == item) {
                    for (vector<string>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
                        cout << (*it2) << endl;
                    }

                    string choice;
                    do {
                        cout << "Entrez le nom de la règle CSS a modifier" << endl;
                        getline(cin, choice);
                    } while (!isItemExist(it->second, choice));

                    if (newValue.find(choice) != string::npos) {
                        newValue.erase(newValue.find(choice),newValue.find(";", newValue.find(choice)) + 2);
                    }
                    newValue += choice + ": " + modifyItem(choice) + "; ";

                    resp = this->yesNoQuestion("Voulez vous modifier d'autres règles CSS ? (yes / no)");

                }
            }
        }


    } else {
        do {
            cout << "Entrez la nouvelle valeur pour l'objet " << item << endl;
            getline(cin, newValue);
        } while (newValue == "");
    }


    
    return newValue;
}

bool functions::yesNoQuestion(string message) {
    string resp;

    do {
        cout << message << endl;
        getline(cin, resp);
        for (int k = 0; k < resp.length(); ++k) {
            tolower(resp[k]);
        }
        if (resp.compare("yes") == 0 || resp.compare("y") == 0 || resp.compare("oui") == 0 || resp.compare("o") == 0)
            return true;
        else if (resp.compare("no") == 0 || resp.compare("n") == 0 || resp.compare("non") == 0)
            return false;
    }
    while (resp.compare("yes") != 0 && resp.compare("y") != 0 && resp.compare("oui") != 0 && resp.compare("o") != 0
           && resp.compare("no") != 0 && resp.compare("n") != 0 && resp.compare("non") != 0);

    return false;
}

bool functions::isItemExist(vector<string> modifiableItems, string item) {
    for (auto it = modifiableItems.begin(); it != modifiableItems.end(); ++it) {
        if (item.compare((*it)) == 0)
            return true;
    }
    return false;
}
