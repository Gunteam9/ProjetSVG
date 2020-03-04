#include "include/serveur.hpp"
#include "include/window.hpp"

#include <iostream>
#include <stdlib.h>
#include <thread>

int main(int argc, char *argv[]){

  Window& w = Window::getInstance();

  w.setWidth(500);
  w.setHeight(500);
  w.setTitre("Moteur de rendu SVG");  

  w.init(&argc, &argv, argv[1]);
   
  Serveur s(argv[1]);


  std::thread t(&Window::start, &w);

  s.startServer(w);

  return 0;
}