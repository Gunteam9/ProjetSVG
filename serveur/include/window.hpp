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

#include "event.hpp"
#include "message.hpp"
#include "serveur.hpp"

namespace constantes {
  constexpr char* RES_DIR = "serveur/resources/";
  constexpr char* MAISON_SVG = "maison.svg";
}


class Window {
    private:
        int taille_x;
        int taille_y;
        std::string titre;
        const char* svg;
        GtkWidget * window;
    public:
        Window(int, int, std::string const&);
        ~Window();
        void init(int*, char***, const char*);
        void start();
        void stop();
        static const char* CURRENT_SVG;

        static tinyxml2::XMLElement* getElementByName(std::vector<tinyxml2::XMLElement*> drivens, std::string const& name){
            for(tinyxml2::XMLElement* driven : drivens){
                if(std::string(driven->Attribute("by")).compare(name) == 0){
                    return driven;
                }
            }
            return NULL;
        }


        static const std::vector<tinyxml2::XMLElement*> getDrivens(tinyxml2::XMLDocument const& document, tinyxml2::XMLElement* const e){
            std::vector<tinyxml2::XMLElement*> drivens;
            if(e != NULL && std::string(e->Name()).compare("driven") == 0 && e->Attribute("by") != NULL){
                drivens.push_back(e);
            }
            if(e->FirstChildElement() != NULL){
                std::vector<tinyxml2::XMLElement*> drivensChildren = getDrivens(document, e->FirstChildElement());
                drivens.insert(drivens.end(), drivensChildren.begin(), drivensChildren.end());
            }
            if(e->NextSiblingElement() != NULL){
                std::vector<tinyxml2::XMLElement*> drivensChildren = getDrivens(document, e->NextSiblingElement());
                drivens.insert(drivens.end(), drivensChildren.begin(), drivensChildren.end());
            }
            return drivens;
        }

        static const std::vector<const char*> getDrivensName(const char* svg){
            tinyxml2::XMLDocument svg_data;
            tinyxml2::XMLPrinter printer;

            std::string chemin(constantes::RES_DIR);
            chemin.append(svg);

            svg_data.LoadFile(chemin.c_str());

            tinyxml2::XMLElement *root = svg_data.RootElement();

            std::vector<tinyxml2::XMLElement*> drivens = getDrivens(svg_data, root);

            std::vector<const char*>  drivensName;

            for(tinyxml2::XMLElement* driven : drivens){
                drivensName.push_back(driven->Attribute("by"));
            }
            return drivensName;
        }

        static void update(std::vector<Message> const& v, const char* svg){
            std::cout << "Nouveau message pour la window" << std::endl;
            
            tinyxml2::XMLDocument svg_data;
            tinyxml2::XMLPrinter printer;

            std::string chemin(constantes::RES_DIR);
            chemin.append(svg);


            svg_data.LoadFile(chemin.c_str());

            tinyxml2::XMLElement *root = svg_data.RootElement();

            std::vector<tinyxml2::XMLElement*> drivens = getDrivens(svg_data, root);
            std::vector<const char*> drivensName = getDrivensName(constantes::MAISON_SVG);

            for(Message m : v){
                tinyxml2::XMLElement *attribut = getElementByName(drivens, m.getNomElement());
                const char* nomAttribut = attribut->Attribute("target");
                attribut->Parent()->ToElement()->SetAttribute(nomAttribut, m.getValeur().c_str());
            }
            
            svg_data.SaveFile(chemin.c_str());
        };
};