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
public:
    const map<const char *, const char *> &getLesElementsDriven() const;

    DataParser();

private:
     std::map<const char *,const  char*> lesElementsDriven;

     static DataParser instance;

     void initColorMap();

     std::map<std::string, std::vector<std::string>(*)(std::string, std::string, double)> interpolationMap;

public:
     static DataParser& getInstance();

     vector<Message> lireMessage(cbor::binary);

     bool validateValue(const char*, const char*);

     std::vector<std::string> interpolate(std::string, std::string, std::string, double);

    cbor::map getCss();

    void setLesElementsDriven(const map<const char *, const char *> &lesElementsDriven);

    std::map<string,std::map<string,string>> getCssValues();

    map<string, std::map<string, string>> getCssValuesReceived();
};

