#include <iostream>
#include <iterator>
#include <fstream>
#include <random>
#include <thread>

#include "../serveur/include/window.hpp"
#include "../serveur/include/dataparser.hpp"
#include "../serveur/include/serveur.hpp"

#include "../client/include/functions.hpp"


int main(int argc, char* argv[]){

    Window& w = Window::getInstance();

    w.setWidth(500);
    w.setHeight(500);
    w.setTitre("Moteur de rendu SVG");
    w.init(&argc, &argv, "dvd.svg");

    DataParser& p = DataParser::getInstance();
    p.setLesElementsDriven(w.getDrivensValue());

    Serveur s("dvd.svg");


    std::thread t(&Window::start, &w);

    std::thread t1(&Serveur::startServer, &s, std::ref(w));

    functions f;

    std::map<std::string, std::string> couleurMap;

    std::ifstream colors("serveur/config/colors.cfg");
    std::string ligne;

    if(colors.is_open()){
        while(getline(colors, ligne)){
            std::string color = ligne.substr(1, ligne.find(":") - 2);
            std::string value = ligne.substr(ligne.find(":") + 3, (ligne.size() - 4) - (ligne.substr(0, ligne.find(":")).size() + 1));
            couleurMap.insert({color, value});
        }
    }else{
        std::cout << "Impossible d'ouvrir le fichier de configuration" << std::endl;
    }

    while(true){
        int i = std::rand() % couleurMap.size();
        std::map<std::string, std::string>::iterator it = std::next(couleurMap.begin(), i);
        f.insertInData(std::string("dvd_fill"), std::string(it->first));
        sleep(2);
        f.sendData();
    }

    t.join();
    t1.join();
    
    return 0;
}

