//
// Created by ionas on 10/02/2020.
//
#pragma once

#include <iostream>
#include "../../vendor/cbor11/cbor11.hpp"

using namespace std;

class Message {
private:
    string nomElement;
    string valeur;

public:
    Message(const string &nomElement, const string &valeur);

    virtual ~Message();

    const string &getNomElement() const;

    const string &getValeur() const;

    friend ostream& operator<<(ostream& os,const Message& p);


};


