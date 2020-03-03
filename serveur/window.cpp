
#include <fcntl.h>
#include <iostream>

#include "include/dataparser.hpp"

#include "include/window.hpp"

RsvgHandle * Window::svg_handle;
tinyxml2::XMLDocument Window::svg_data;

Window::Window(int taille_x, int taille_y, std::string const& titre) : taille_x(taille_x), taille_y(taille_y), titre(titre){
}

Window::~Window(){
}

static void do_drawing_svg(cairo_t * cr, RsvgHandle * svg_handle, int tx, int ty)
{
    tinyxml2::XMLPrinter printer;

    Window::svg_data.Print(&printer);

    svg_handle = rsvg_handle_new_from_data ((const unsigned char*) printer.CStr(), printer.CStrSize()-1, NULL);

    tinyxml2::XMLElement* svg = Window::svg_data.FirstChildElement();

    std::string width = svg->Attribute("width");
    std::string height = svg->Attribute("height");

    int x = std::stoi(width);
    int y = std::stoi(height);

    cairo_translate(cr, tx/2 - x/2, ty/2 - y/2);

    rsvg_handle_render_cairo(svg_handle, cr);
    
}

static void do_drawing(cairo_t* cr, int tx, int ty){
    do_drawing_svg(cr, Window::svg_handle, tx, ty);
}

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data){
    GtkWindow* w = GTK_WINDOW(user_data);
    int x, y ;
    gtk_window_get_size(w, &x, &y);
    do_drawing(cr, x, y);
    return FALSE;
}

void Window::init(int* argc, char*** argv, const char* svg){

    gtk_init(argc, argv);

    Window::window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    this->darea = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(Window::window), this->darea);

    std::string chemin(constantes::RES_DIR);
    chemin.append(svg);

    tinyxml2::XMLPrinter printer;

    Window::svg_data.LoadFile(chemin.c_str());
    Window::svg_data.Print(&printer);
    Window::svg_handle = rsvg_handle_new_from_data ((const unsigned char*) printer.CStr(), printer.CStrSize()-1, NULL);
    

    g_signal_connect(G_OBJECT(this->darea), "draw", 
        G_CALLBACK(on_draw_event), Window::window);
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

tinyxml2::XMLElement* Window::getElementByName(std::vector<tinyxml2::XMLElement*> drivens, std::string const& name){
    for(tinyxml2::XMLElement* driven : drivens){
        if(std::string(driven->Attribute("by")).compare(name) == 0){
            return driven;
        }
    }
    return NULL;
}


const std::vector<tinyxml2::XMLElement*> Window::getDrivens(tinyxml2::XMLDocument const& document, tinyxml2::XMLElement* const e){
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

const std::vector<const char*> Window::getDrivensName(const char* svg){
    tinyxml2::XMLElement *root = Window::svg_data.RootElement();

    std::vector<tinyxml2::XMLElement*> drivens = getDrivens(svg_data, root);

    std::vector<const char*>  drivensName;

    for(tinyxml2::XMLElement* driven : drivens){
        drivensName.push_back(driven->Attribute("by"));
    }
    return drivensName;
}

void Window::update(std::vector<Message> const& v, const char* svg){
    std::cout << "Nouveau message pour la window" << std::endl;

    tinyxml2::XMLElement *root = Window::svg_data.RootElement();

    std::vector<tinyxml2::XMLElement*> drivens = getDrivens(Window::svg_data, root);
    std::vector<const char*> drivensName = getDrivensName(constantes::MAISON_SVG);

    for(Message m : v){
        tinyxml2::XMLElement* attribut = getElementByName(drivens, m.getNomElement());
        const char* nomAttribut = attribut->Attribute("target");
        attribut->Parent()->ToElement()->SetAttribute(nomAttribut, m.getValeur().c_str());
    }

};