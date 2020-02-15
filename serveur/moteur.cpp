#include "include/window.hpp"
#include "include/serveur.hpp"

#include <iostream>
#include <stdlib.h>
#include <thread>

int main(int argc, char *argv[]){
  Window w(500, 500, "Moteur de rendu SVG"); 
  Serveur s;
  std::thread t(&Serveur::startServer, &s);
  w.init(&argc, &argv, s);
  Message m("test", "1");
  //w.update({m});
  w.start();
  //std::cout << "hello" << std::endl;
  w.stop();

  return 0;
}