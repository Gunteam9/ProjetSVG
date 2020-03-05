#pragma once

#include <librsvg/rsvg.h>
#include <cairo.h>
#include <gtk/gtk.h>
#include <gio/gfile.h>
#include <tinyxml2.h>

#include <stdlib.h>
#include <vector>
#include <string>

#include "message.hpp"

namespace constantes {
  constexpr const char* RES_DIR = "serveur/resources/";
}

class Window {
    private:
        int taille_x;
        int taille_y;
        std::string titre;

        GdkPixbuf* icon;
        GtkWidget* window;
        RsvgHandle *svg_handle;
        tinyxml2::XMLDocument svg_data;
        GtkWidget* darea;

        Window();
        
    public:
        static Window& getInstance();
        ~Window();
        
        void init(int*, char***, const char*);

        void start();
        void stop();

        tinyxml2::XMLElement* getElementByName(std::vector<tinyxml2::XMLElement*>, std::string const&);
        
        const std::vector<const char*> getDrivensName();

        const std::map<const char*, const char*> getDrivensValue();
        
        const std::vector<tinyxml2::XMLElement*> getDrivens(tinyxml2::XMLDocument const&, tinyxml2::XMLElement* const);
        
        void update(std::vector<Message> const&);

        //SETTERS
        void setWidth(int);
        void setHeight(int);
        void setTitre(std::string);


    // GETTERS
        RsvgHandle* getSvgHandle();
        tinyxml2::XMLDocument* getSvgData();
        GtkWidget* getDarea();
        GtkWidget* getWindow();

};