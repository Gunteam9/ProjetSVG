#include "include/window.hpp"
#include "include/serveur.hpp"

#include <iostream>
#include <stdlib.h>
#include <thread>

int main(int argc, char *argv[]){

  Window w(500, 500, "Moteur de rendu SVG"); 
  Serveur s;
  w.init(&argc, &argv, constantes::MAISON_SVG);
  std::thread t(&Window::start, &w);
  s.startServer();
  return 0;
}