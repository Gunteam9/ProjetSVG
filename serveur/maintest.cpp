//
// Created by ionas on 10/02/2020.
//







#include "include/dataparser.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    DataParser p ;
    cbor::map map = {{"jeuis", "une map"},{"jesuis2","une deuxime valeur"}};
    cbor::binary encoded  = cbor::encode(map);

    vector<Message> m = p.lireMessage(encoded);
    cout <<m[0] <<endl;

    //cout <<m[1]<<endl;
}



