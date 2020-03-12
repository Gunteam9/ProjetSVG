//
// Created by ionas on 10/02/2020.
//

#pragma once

#include "message.hpp"
#include <stdlib.h>
#include <map>
#include "../../vendor/cbor11/cbor11.hpp"
#include "../../vendor/exceptions/errorException.hpp"
#include "window.hpp"

static std::map<std::string, std::string> COULEURS_MAP;

class DataParser {

private:
     static DataParser instance;

     void initColorMap();

     std::map<std::string, std::vector<std::string>(*)(std::string, std::string, double)> interpolationMap;

     DataParser();
public:
     static DataParser getInstance();

     vector<Message> lireMessage(cbor::binary);

     bool validateValue(const char*, const char*);

     std::vector<std::string> interpolate(std::string, std::string, std::string, double);

    cbor::map getCss();
};

