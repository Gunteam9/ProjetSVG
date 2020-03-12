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

  std::cout << std::stod("0.3") << std::endl;
  std::string str = "0.3";
  double d = std::stod(str);
  std::cout << d << std::endl;

  //w.setIcon("maison.svg");

  w.init(&argc, &argv, argv[1]);
   
  Serveur s(argv[1]);


  std::thread t(&Window::start, &w);

  s.startServer(w);

  return 0;
}