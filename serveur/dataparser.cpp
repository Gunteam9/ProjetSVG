//
// Created by ionas on 10/02/2020.
//


#include "dataparser.hpp"
/**
 * Méthode qui prend un cbor encodé, le cbor doit être une map d'élément valeur
 * @param encodedItem est le cbor encodé
 * @return un tableau des messages
 */
vector<Message> DataParser::lireMessage(cbor::binary encodedItem) {
    
    cbor decodedItem= cbor::decode(encodedItem);

    if(!decodedItem.is_map()){
        throw ErreurException("encodedItem doit être une map encodée");
    }

    map<cbor,cbor> maMap = decodedItem;

    vector<Message> mesMessages;

    mesMessages.reserve(maMap.size());

    map<cbor,cbor>::iterator it = maMap.begin();

    while (it != maMap.end()){
        string element = it->first;
        string valeur = it->second;

        Message m(element,valeur);
        mesMessages.push_back(m);
        it++;
    }

    return mesMessages;
}
