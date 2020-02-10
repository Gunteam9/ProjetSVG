//
// Created by ionas on 10/02/2020.
//

#pragma once

#include "message.hpp"
#include "../cbor11/cbor11.hpp"
#include "../erreur/erreur.hpp"


class DataParser {

public:
     vector<Message> lireMessage(cbor::binary encodedItem);

};

