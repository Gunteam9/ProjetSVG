#include "window.hpp"

#include <iostream>

int main(int argc, char *argv[]){
  Window w(500, 500); 
  w.init(&argc, &argv);
  w.start();
  std::cout << "hello" << std::endl;
  w.stop();

  return 0;
}