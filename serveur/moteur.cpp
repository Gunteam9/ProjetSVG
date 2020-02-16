#include "include/window.hpp"
#include "include/serveur.hpp"

#include <iostream>
#include <stdlib.h>
#include <thread>

int main(int argc, char *argv[]){
  Window w(500, 500, "Moteur de rendu SVG"); 
  Serveur s;
  std::thread t(&Serveur::startServer, &s);
  w.start();
  w.stop();

  return 0;
}