
#include "include/dataparser.hpp"

#include "include/window.hpp"

Window::Window(int taille_x, int taille_y, std::string const& titre) : taille_x(taille_x), taille_y(taille_y), titre(titre){
}

Window::~Window(){
}

static void do_drawing_svg(cairo_t * cr, RsvgHandle * svg_handle, int tx, int ty)
{ 
    tinyxml2::XMLDocument svg_data;
    tinyxml2::XMLPrinter printer;

    std::filesystem::path chemin;
    chemin.append(constantes::RES_DIR);
    chemin.append(constantes::MAISON_SVG);

    svg_data.LoadFile(chemin.c_str());

    svg_data.Print(&printer);

    svg_handle = rsvg_handle_new_from_data ((const unsigned char*) printer.CStr(), printer.CStrSize()-1, NULL);

    tinyxml2::XMLElement* svg = svg_data.FirstChildElement();

    std::string width = svg->Attribute("width");
    std::string height = svg->Attribute("height");

    int x = std::stoi(width);
    int y = std::stoi(height);

    cairo_translate(cr, tx/2 - x/2, ty/2 - y/2);

    rsvg_handle_render_cairo(svg_handle, cr);
    
}

static void do_drawing(cairo_t* cr, int tx, int ty){
    do_drawing_svg(cr, svg_handle, tx, ty);
}

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data){
    GtkWindow* w = GTK_WINDOW(user_data);
    int x, y;
    gtk_window_get_size(w, &x, &y);
    do_drawing(cr, x, y);
    return FALSE;
}

void Window::init(int* argc, char*** argv){
    GtkWidget *darea;

    gtk_init(argc, argv);

    this->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    darea = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(this->window), darea);


    tinyxml2::XMLDocument svg_data;
    tinyxml2::XMLPrinter printer;

    std::filesystem::path chemin;
    chemin.append(constantes::RES_DIR);
    chemin.append(constantes::MAISON_SVG);

    svg_data.LoadFile(chemin.c_str());
    svg_data.Print(&printer);
    svg_handle = rsvg_handle_new_from_data ((const unsigned char*) printer.CStr(), printer.CStrSize()-1, NULL);
    
    g_signal_connect(G_OBJECT(darea), "draw", 
        G_CALLBACK(on_draw_event), this->window);
    g_signal_connect(this->window, "destroy",
        G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT (this->window), "delete_event",
        G_CALLBACK (gtk_main_quit), NULL);

    gtk_window_set_position(GTK_WINDOW(this->window), GTK_WIN_POS_CENTER);

    gtk_window_set_default_size(GTK_WINDOW(this->window), this->taille_x, this->taille_y);

    gtk_window_set_title(GTK_WINDOW(this->window), this->titre.c_str());

    gtk_widget_show_all(this->window);
}

void Window::start(){
    gtk_main();
}

void Window::stop(){
    gtk_widget_destroy(this->window);
}