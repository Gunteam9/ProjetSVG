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

#define PORT     6789
#define MAXLINE 1024

using namespace std;

int main(int argc, char *argv[]) {
    Serveur s;
    s.startServer();

}



