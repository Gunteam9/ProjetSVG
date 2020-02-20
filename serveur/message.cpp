//
// Created by ionas on 10/02/2020.
//

#include "include/message.hpp"

Message::~Message() = default;

Message::Message(const string &nomElement, const string &valeur) : nomElement(nomElement), valeur(valeur) {}


const string &Message::getNomElement() const {
    return nomElement;
}

const string &Message::getValeur() const {
    return valeur;
}

ostream &operator<<(ostream &os, const Message &p) {
    os << "Element : "<< p.nomElement << " | Valeur : " << p.valeur;
    return os;
}
