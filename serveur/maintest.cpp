//
// Created by ionas on 10/02/2020.
//





#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include "../exceptions/erreurException.hpp"
#include "serveur.hpp"
#include "../cbor11/cbor11.hpp"
#include "dataparser.hpp"

#define PORT     6789
#define MAXLINE 1024

using namespace std;

int main(int argc, char *argv[]) {
    cbor::map test = cbor::map {{"salut","oui"}};
    cout << test.at("salut").to_string();
}



