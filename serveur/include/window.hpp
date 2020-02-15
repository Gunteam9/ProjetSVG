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

class Window {
    private:
        int taille_x;
        int taille_y;
        std::string titre;
        //GtkWidget * window;
        std::queue<int *> eventQueue;
        tinyxml2::XMLElement* getElementByName(tinyxml2::XMLDocument const&, std::string const&, tinyxml2::XMLElement* const);
        //int viderPile(_GIOChannel*, GIOCondition, void*);
    public:
        Window(int, int, std::string const&);
        ~Window();
        void init(int*, char***, Serveur const&);
        void start();
        void stop();
        void update(std::vector<Message> const&);
        int actualiserServeur();
};