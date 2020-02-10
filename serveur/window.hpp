#include <librsvg/rsvg.h>
#include <cairo.h>
#include <gtk/gtk.h>
#include <gio/gfile.h>
#include <tinyxml2.h>
#include <iostream>

class Window {
    private:
        int taille_x;
        int taille_y;
        GtkWidget * window;
    public:
        Window(int, int);
        ~Window();
        void init(int*, char***);
        void start();
        void stop();
};