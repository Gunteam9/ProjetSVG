//
// Created by gunteam on 05/02/2020.
//

#pragma once

#include <algorithm>
#include <string>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include "../../vendor/cbor11/cbor11.hpp"
#include "../../vendor/exceptions/udpRuntimeException.hpp"
#include "../../vendor/exceptions/udpSendingException.hpp"
#include "../../vendor/exceptions/udpBindsException.hpp"
#include "../../vendor/exceptions/udpAdresseConvertionException.hpp"
#include "../../vendor/exceptions/udpConnectionException.hpp"
#include "../../vendor/exceptions/udpReceiveException.hpp"
#include "../../vendor/exceptions/udpReceiveException.hpp"
#include "../../serveur/include/dataparser.hpp"
#include "../../serveur/include/message.hpp"


#define PORT 6789
#define IP_SERVER "127.0.0.2"
#define IP_CLIENT "127.0.0.3"

#define FIRST_DELIMITER ": "
#define SECOND_DELIMITER " "
#define MAIN_DELIMITER "\n"

class functions {
public:
    functions();
    virtual ~functions();

    //Données
    void sendData();
    void insertInData(const std::string& item, const std::string& value);
    void deleteEntry(const std::string& key);

    //Utile
    bool isItemExist(const vector<std::string> &vectorOfItem, const string &item);
    bool yesNoQuestion(const std::string& message);
    bool isStyleItem(const string& item);

    vector<std::string> getStyleElements(const std::string& item);

    //Getters and setters
    const vector<string> &getDrivensItems();

private:

    //Socket
    int sock = 0;
    //Addresse du serveur
    struct sockaddr_in serv_addr{};

    //Données à envoyer
    cbor::map data;

    //Items
    vector<std::string> drivensItems;
    map<std::string, vector<std::string>> styleItems;

    //Informations serveur
    void getModifiableInformations();

};