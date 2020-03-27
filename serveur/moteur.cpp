#include "include/serveur.hpp"
#include "include/window.hpp"


#include <thread>

int main(int argc, char *argv[]){

  Window& w = Window::getInstance();

  w.setWidth(500);
  w.setHeight(500);
  w.setTitre("Moteur de rendu SVG");
  w.init(&argc, &argv, argv[1]);

  DataParser& p = DataParser::getInstance();
  p.setLesElementsDriven(w.getDrivensValue());

  std::thread t(&Window::start, &w);

  Serveur s(argv[1]);
  s.startServer(w);

  return 0;
}