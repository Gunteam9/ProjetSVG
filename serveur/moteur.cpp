#include "include/serveur.hpp"
#include "include/window.hpp"

#include <iostream>
#include <stdlib.h>
#include <thread>

int main(int argc, char *argv[]){

  Window w(500, 500, "Moteur de rendu SVG"); 
  Serveur s(constantes::MAISON_SVG);
  w.init(&argc, &argv, constantes::MAISON_SVG);
  std::thread t(&Window::start, &w);
  s.startServer(w);
  return 0;
}