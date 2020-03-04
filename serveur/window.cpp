
#include <iostream>

#include "include/dataparser.hpp"

#include "include/window.hpp"

Window::Window(){

}

Window::~Window(){
}

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

Window& Window::getInstance(){
    static Window w;
    return w;
}

void Window::init(int* argc, char*** argv, const char* svg){

    gtk_init(argc, argv);

    this->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    this->darea = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(Window::window), this->darea);

    std::string chemin(constantes::RES_DIR);
    chemin.append(svg);

    tinyxml2::XMLPrinter printer;

    this->svg_data.LoadFile(chemin.c_str());
    this->svg_data.Print(&printer);
    this->svg_handle = rsvg_handle_new_from_data ((const unsigned char*) printer.CStr(), printer.CStrSize()-1, NULL);

    g_signal_connect(G_OBJECT(this->darea), "draw", 
        G_CALLBACK(on_draw_event), this);
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
    
    gtk_widget_queue_draw(Window::darea);
};

void Window::setWidth(int w){
    this->taille_x = w;
}
void Window::setHeight(int h){
    this->taille_y = h;
}
void Window::setTitre(std::string t){
    this->titre = t;
}

RsvgHandle* Window::getSvgHandle(){
    return this->svg_handle;
}

tinyxml2::XMLDocument* Window::getSvgData(){
    return &this->svg_data;
}

GtkWidget* Window::getDarea(){
    return this->darea;
}

GtkWidget* Window::getWindow(){
    return this->window;
}