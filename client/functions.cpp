//
// Created by gunteam on 05/02/2020.
// Source (réseau): https://bousk.developpez.com/cours/reseau-c++/UDP/01-introduction-premiers-pas/ - https://bousk.developpez.com/cours/reseau-c++/TCP/04-serveur-premiers-pas
//
#include "include/functions.hpp"


using namespace std;

/**
 * Generate socket
 */
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

    data = { { "?", "?"} };

    sendData();

}

/**
 * Default constructor
 */
functions::~functions() = default;

/**
 * Send Data to the server
 * @param data - data to send
 */
void functions::sendData() {

    /* Debug
    for (auto it = data.begin(); it != data.end(); ++it) {
        cout << (string) it->first << " " << (string) it->second << endl;
    }
     */

    cbor::binary encoded = cbor::encode(data);

    // Envoie de message
    if (sendto(sock, encoded.data(), encoded.size(), 0, (const sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
        throw udpSendingException();
    }
    cout << "Message envoyé" << endl;


    // Réception des informations modifiables
    if (data.begin()->first == "?") {
        data = {};
        getModifiableInformations();
    }
    this->data.clear();
}


/**
 * Get and save data from the server
 * Modify drivensItems and styleItems
 */
void functions::getModifiableInformations() {

    char buffer[1024] = {0};

    //Réception des données du serveur (hors paramètre de style)
    if (recv(sock, buffer, sizeof(buffer), 0) < 0) {
        throw udpReceiveException("Impossible de recevoir les éléments driven");
    }

    string element = (string) buffer;

    //Stockage dans un vector<string> des éléments simple
    while (element.length() != 0) {
        this->drivensItems.push_back(element.substr(0, element.find_first_of(MAIN_DELIMITER)));
        element.erase(0, (int) element.find_first_of(MAIN_DELIMITER)+1);
    }

    char buffer2[1024] = {0};

    //Réception des données du serveur (uniquement paramètre de style)
    if (recv(sock, buffer2, sizeof(buffer2), 0) < 0) {
        throw udpReceiveException("Impossible de recevoir les éléments de style");
    }

    element = (string) buffer2;

    vector<string> vectorStyleItems;

    //Suppression de la 1ère phrase de présentation
    element.erase(0, element.find_first_of(MAIN_DELIMITER) + 1);

    //Stockage des éléments dans une map<string, vector<string> >
    //En clef: l'élément en question
    //En valeur, un vector<string> des paramètres CSS (margin, padding, etc)
    while(element.length() != 0) {
        string key = element.substr(0, element.find_first_of(FIRST_DELIMITER));
        element.erase(0, element.find_first_of(FIRST_DELIMITER) + 2);
        string value = element.substr(0, element.find_first_of(MAIN_DELIMITER));
        element.erase(0, element.find_first_of(MAIN_DELIMITER) + 1);

        while(value.length() != 0) {
            vectorStyleItems.push_back(value.substr(0, value.find_first_of(SECOND_DELIMITER)));
            value.erase(0, (int) value.find_first_of(SECOND_DELIMITER) + 1);
        }

        styleItems.insert({key, vectorStyleItems});
        element.erase(0, (int) element.find_first_of(MAIN_DELIMITER) + 1);
    }
}

//////////////////////////////////////////////
//                                          //
//                                          //
//                  UTILS                   //
//                                          //
//                                          //
//////////////////////////////////////////////

/**
 * To ask yes no question
 * Accepted position answer: yes / y / oui / o / YES / Y / OUI / O
 * Accepted negative anser: no / n / non / NO / N / NON
 * Linux Like
 *
 * @param message - Question
 * @return Answer (true / false)
 */
bool functions::yesNoQuestion(const string& message) {
    string resp;

    do {
        cout << message << endl;
        getline(cin, resp);

        //Change la casse du mot pour les comparaisons d'après
        for (char k : resp) {
            tolower(k);
        }
        if (resp == "yes" || resp == "y" || resp == "oui" || resp == "o")
            return true;
        else if (resp == "no" || resp == "n" || resp == "non")
            return false;
    }
    while (resp != "yes" && resp != "y" && resp !="oui" && resp !="o" && resp !="no"  && resp != "n" && resp != "non");

    return false;
}

/**
 * Return true if the given item exists in the given list
 * @param modifiableItems - List (vector<string>)
 * @param item - Item (string)
 * @return True if the item is in the list
 */
bool functions::isItemExist(const vector<string>& vectorOfItem, const string& item) {
    for (const auto & it : vectorOfItem) {
        if (item == it)
            return true;
    }
    return false;
}

/**
 *
 * @param item
 * @return Return true if the specified item is a styleItem
 */
bool functions::isStyleItem(const string& item) {
    //Si l'item se termine par _style et que son nom est plus long que 6 (sinon exception dans le item.compare)
    return item.length() > 6 && item.compare(item.length() - 6, 6, "_style") == 0;
}

/**
 *
 * @param item
 * @return Return a vector<string> who contains all the style element for the specified item
 * @throw Throw a errorException if the speficied item is not a style Item
 */
vector<std::string> functions::getStyleElements(const string& item) {

    //Trouve le bon item parmi ceux existant
    for (auto & styleItem : styleItems) {
        if (item == styleItem.first)
            return styleItem.second;
    }

    throw errorException("L'item n'est pas un élément de style");
}

//////////////////////////////////////////////
//                                          //
//                                          //
//           GETTERS AND SETTERS            //
//                                          //
//                                          //
//////////////////////////////////////////////

/**
 *
 * @return drivensItems
 */
const vector<string> &functions::getDrivensItems() {
    return drivensItems;
}

/**
 *
 * @param item
 * @param value
 */
void functions::insertInData(const string& item, const string& value) {
    data.insert({item, value});
}