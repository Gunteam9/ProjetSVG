#include <librsvg/rsvg.h>
#include <cairo.h>
#include <gtk/gtk.h>
#include <gio/gfile.h>
#include <tinyxml2.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <queue>
#include <filesystem>

#include "event.hpp"
#include "message.hpp"
#include "serveur.hpp"

namespace constantes {
  constexpr const char* RES_DIR = "serveur/resources/";
  constexpr const char* MAISON_SVG = "maison.svg";
}

class Window {
    private:
        int taille_x;
        int taille_y;
        std::string titre;
        GtkWidget * window;
    public:
        Window(int, int, std::string const&);
        ~Window();
        void init(int*, char***);
        void start();
        void stop();

        static tinyxml2::XMLElement* getElementByName(tinyxml2::XMLDocument const& document, std::string const& name, tinyxml2::XMLElement* const e){
            if(e != NULL && std::string(e->Name()).compare("driven") == 0 && e->Attribute("by") != NULL && std::string(e->Attribute("by")).compare(name) == 0){
                return e;
            }else{
                if(e->FirstChildElement() != NULL){
                    tinyxml2::XMLElement* children = getElementByName(document, name, e->FirstChildElement());
                    if(children != NULL){
                        return children;
                    }
                }
                if(e->NextSiblingElement() != NULL){
                    tinyxml2::XMLElement* siblings = getElementByName(document, name, e->NextSiblingElement());
                    if(siblings != NULL){
                        return siblings;
                    }
                }
            }
            return NULL;
        }

        static void update(std::vector<Message> const& v){
            std::cout << "Nouveau message pour la window" << std::endl;
            
            tinyxml2::XMLDocument svg_data;
            tinyxml2::XMLPrinter printer;

            std::filesystem::path chemin;
            chemin.append(constantes::RES_DIR);
            chemin.append(constantes::MAISON_SVG);

            svg_data.LoadFile(chemin.c_str());

            tinyxml2::XMLElement *root = svg_data.RootElement();

            for(Message m : v){
                tinyxml2::XMLElement *attribut = getElementByName(svg_data, m.getNomElement(), root);
                const char* nomAttribut = attribut->Attribute("target");
                attribut->Parent()->ToElement()->SetAttribute(nomAttribut, m.getValeur().c_str());
            }
            
            svg_data.SaveFile(chemin.c_str());
        };
};