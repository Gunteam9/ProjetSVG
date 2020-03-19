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


}

/**
 * Default constructor
 */
functions::~functions() = default;

/**
 * Send Data to the server
 * @param data - data to send
 */
void functions::sendData(const cbor::map & data) {

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
    if (data.begin()->first == "?")
        getModifiableInformations();
}


/**
 * Get and save data from the server
 */
void functions::getModifiableInformations() {

    char buffer[1024] = {0};

    //Réception des données du serveur (hors paramètre de style)
    if (recv(sock, buffer, sizeof(buffer), 0) < 0) {
        throw udpReceiveException("Impossible de recevoir les éléments driven");
    }

    string element = (string) buffer;
    string delimiter = "\n";
    vector<string> modifiableItems;

    //Stockage dans un vector<string> des éléments simple
    while (element.length() != 0) {
        modifiableItems.push_back(element.substr(0, element.find_first_of(delimiter)));
        element.erase(0, (int) element.find_first_of(delimiter)+1);
    }

    char buffer2[1024] = {0};

    //Réception des données du serveur (uniquement paramètre de style)
    if (recv(sock, buffer2, sizeof(buffer2), 0) < 0) {
        throw udpReceiveException("Impossible de recevoir les éléments de style");
    }

    element = (string) buffer2;

    string firstDelimiter = ": ";
    string secondDelimiter = " ";
    string mainDelimiter = "\n";

    vector<string> vectorStyleItems;

    //Suppression de la 1ère phrase de présentation
    element.erase(0, element.find_first_of(mainDelimiter) + 1);

    //Stockage des éléments dans une map<string, vector<string> >
    //En clef: l'élément en question
    //En valeur, un vector<string> des paramètres CSS (margin, padding, etc)
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

    //Demande à l'utilisateur les modifications à effectuer
    showModifiableItems(modifiableItems);

}


/**
 * Print and select modifiables items
 * @param modifiableItems - Liste des items modifiables
 */
void functions::showModifiableItems(vector<string> modifiableItems) {

    //Affichage des éléments modifiables
    for (auto & modifiableItem : modifiableItems) {
        cout << modifiableItem << endl;
    }

    //Choix de l'item à modifier
    string choice;
    do {
        cout << "Entrez le nom de l'item a modifier" << endl;
        getline(cin, choice);
    } while (!isItemExist(modifiableItems, choice));

    //Modifie les items (via la fonction modifyItem)
    //Les ajoute dans la map de données pour envoyer au serveur
    for(auto & modifiableItem : modifiableItems) {
        if(choice == modifiableItem){
            string mapValueToSend = modifyItem(choice);
            if  (!mapValueToSend.empty())
                data.insert({choice, mapValueToSend});
            break;
        }
    }

    //Demande à l'utilisateur si il souhaite en modifier d'autres
    //Sinon, envoie les données au serveur (puis le client se ferme)
    bool resp = this->yesNoQuestion("Voulez vous modifier d'autres item ? (yes / no)");
    if (resp)
        showModifiableItems(modifiableItems);
    else
        sendData(data);


}

/**
 * Assign a new value to the specified item
 * @param item
 * @return the new Value
 */
string functions::modifyItem(const string& item){
    string newValue;
    bool resp = true;

    //Si l'item se termine par _style et que son nom est plus long que 6 (sinon exception dans le item.compare)
    if (item.length() > 6 && item.compare(item.length()-6, 6, "_style") == 0) {

        //Si l'élément de style contient des règles CSS
        if (!this->styleItems.empty()) {

            //Si on souhaite modifier plusieurs règles CSS
            while (resp) {
                cout << "Liste des éléments CSS modifiables: " << endl;

                //Trouve le bon item parmi ceux existant
                for (map<string, vector<string> >::iterator it = this->styleItems.begin();
                     it != this->styleItems.end(); ++it) {
                    if (it->first == item) {

                        //Liste les éléments CSS modifiables pour l'item concerné
                        for (vector<string>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
                            cout << (*it2) << endl;
                        }

                        //Choix de l'utilisateur
                        string choice;
                        do {
                            cout << "Entrez le nom de la règle CSS a modifier" << endl;
                            getline(cin, choice);
                        } while (!isItemExist(it->second, choice));

                        //Si l'item a déjà été modifié dans la même session, on supprime l'ancienne valeur et concerve la nouvelle
                        if (newValue.find(choice) != string::npos) {
                            newValue.erase(newValue.find(choice), newValue.find(";", newValue.find(choice)) + 2);
                        }

                        //Ré invoque la fonction pour considérer l'élément CSS comme un item classique
                        // + Mise en forme pour la map pour le serveur
                        newValue += choice + ": " + modifyItem(choice) + "; ";

                        resp = this->yesNoQuestion("Voulez vous modifier d'autres règles CSS ? (yes / no)");

                    }
                }
            }
        } else {
            cout << "Cet élément driven ne contient pas de règle de style" << endl;
            newValue = "";
        }

    //Pour les item simple
    } else {
        do {
            cout << "Entrez la nouvelle valeur pour l'objet " << item << endl;
            getline(cin, newValue);
        } while (newValue.empty());
    }


    
    return newValue;
}


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
bool functions::isItemExist(const vector<string>& modifiableItems, const string& item) {
    for (auto it = modifiableItems.begin(); it != modifiableItems.end(); ++it) {
        if (item == *it)
            return true;
    }
    return false;
}
