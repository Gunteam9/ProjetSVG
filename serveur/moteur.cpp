#include "window.hpp"

#include <iostream>

int main(int argc, char *argv[]){
  Window w(500, 500, "Moteur de rendu SVG"); 
  w.init(&argc, &argv);
  w.start();
  Message m("test", "1");
  w.update({m});
  std::cout << "hello" << std::endl;
  w.stop();

  return 0;
}