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

  //w.setIcon("maison.svg");

  w.init(&argc, &argv, argv[1]);
   
  Serveur s(argv[1]);

  DataParser d= DataParser::getInstance();
  cbor::map m = d.getCss();
  std::map<cbor,cbor> m1 = m ;
  std::string s1 = m1.begin()->first;
  std::vector<cbor> v = m1.begin()->second ;
  std::string premiere_value = v[0];

  cout<<s1 << " et "<< premiere_value<<endl;

  std::thread t(&Window::start, &w);

  s.startServer(w);

  return 0;
}