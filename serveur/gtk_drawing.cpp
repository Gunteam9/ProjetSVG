#include <librsvg/rsvg.h>
#include <cairo.h>
#include <gtk/gtk.h>
#include <gio/gfile.h>
#include <tinyxml2.h>

#include <iostream>
#include <stdlib.h>

#include "include/window.hpp"

static void do_drawing_svg(cairo_t * cr, RsvgHandle * svg_handle, int tx, int ty, Window& w)
{
    tinyxml2::XMLPrinter printer;

    w.getSvgData()->Print(&printer);

    svg_handle = rsvg_handle_new_from_data ((const unsigned char*) printer.CStr(), printer.CStrSize()-1, NULL);

    tinyxml2::XMLElement* svg =  w.getSvgData()->FirstChildElement();

    std::string width = svg->Attribute("width");
    std::string height = svg->Attribute("height");

    int x = std::stoi(width);
    int y = std::stoi(height);

    cairo_translate(cr, tx/2 - x/2, ty/2 - y/2);

    std::cout <<  "ERREUR TYPE " << RSVG_TYPE_ERROR << std::endl;
    std::cout <<  "ERREUR FAILED " << RSVG_ERROR_FAILED << std::endl;
    std::cout << "ERREUR QUARK " << g_quark_to_string(RSVG_ERROR) << std::endl;

    std::cout << cairo_status(cr) << std::endl;
    rsvg_handle_render_cairo(svg_handle, cr);

}

static void do_drawing(cairo_t* cr, int tx, int ty, Window& w){
    do_drawing_svg(cr, w.getSvgHandle(), tx, ty, w);
}

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data){
    Window* w = static_cast<Window*>(user_data);
    GtkWindow* window = GTK_WINDOW(w->getWindow());
    int x, y ;
    gtk_window_get_size(window, &x, &y);
    do_drawing(cr, x, y, *w);
    return FALSE;
}