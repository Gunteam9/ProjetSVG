#include <librsvg/rsvg.h>
#include <cairo.h>
#include <gtk/gtk.h>
#include <gio/gfile.h>
#include <tinyxml2.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>

#include "./message.hpp"

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
        void update(std::vector<Message> const&);
};