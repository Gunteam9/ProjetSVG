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


class functions {
public:
    functions();
    virtual ~functions();

    void sendData(cbor::map data);


private:

    //Socket
    int sock = 0;

    //Addresse du serveur
    struct sockaddr_in serv_addr;

    void getModifiableInformations();
    void showModifiableItems(vector<std::string> modifiableItems);
    string modifyItem(std::string item);

    bool isItemExist(vector<std::string> modifiableItems, std::string item);

};