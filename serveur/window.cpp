
#include "include/dataparser.hpp"

#include "include/window.hpp"

Window::Window(int taille_x, int taille_y, std::string const& titre){
    this->taille_x = taille_x;
    this->taille_y = taille_y;
    this->titre = titre;
}

Window::~Window(){
    
}

static RsvgHandle *svg_handle;
static GtkWidget* window;

static void do_drawing_svg(cairo_t * cr, RsvgHandle * svg_handle)
{ 
    tinyxml2::XMLDocument svg_data;
    tinyxml2::XMLPrinter printer;

    svg_data.LoadFile("resources/maison.svg");

    //tinyxml2::XMLElement *rectangle = svg_data.FirstChildElement("svg")->FirstChildElement("g")->FirstChildElement("rect");
    tinyxml2::XMLElement *rectangle = svg_data.FirstChild()->FirstChild()->NextSibling()->FirstChildElement("rect");
    //rectangle->SetAttribute("style", "fill:#424242");
    rectangle->SetAttribute("fill", "red");
    svg_data.Print(&printer);
    svg_handle = rsvg_handle_new_from_data ((const unsigned char*) printer.CStr(), printer.CStrSize()-1, NULL);

    rsvg_handle_render_cairo(svg_handle, cr);
    
}

static void do_drawing(cairo_t* cr){
    cairo_move_to (cr, 100.0, 150.0);
    cairo_select_font_face (cr, "serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_show_text(cr, "Hello world !");
    do_drawing_svg(cr, svg_handle);
    cairo_move_to (cr, 0.0, 0.0);
}

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, 
    gpointer user_data)
{
    do_drawing(cr);
    return FALSE;
}


void Window::init(int* argc, char*** argv){
    GtkWidget *darea;

    gtk_init(argc, argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    darea = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(window), darea);


    tinyxml2::XMLDocument svg_data;
    tinyxml2::XMLPrinter printer;

    svg_data.LoadFile("resources/maison.svg");
    svg_data.Print(&printer);
    svg_handle = rsvg_handle_new_from_data ((const unsigned char*) printer.CStr(), printer.CStrSize()-1, NULL);
    
    
    g_signal_connect(G_OBJECT(darea), "draw", 
        G_CALLBACK(on_draw_event), NULL);
    g_signal_connect(window, "destroy",
        G_CALLBACK(gtk_main_quit), NULL);

    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    gtk_window_set_default_size(GTK_WINDOW(window), this->taille_x, this->taille_y);

    gtk_window_set_title(GTK_WINDOW(window), this->titre.c_str());

    gtk_widget_show_all(window);
}

void Window::start(){
    gtk_main();
}

void Window::stop(){
    gtk_widget_destroy(window);
}

void Window::update(std::vector<Message> const& messages){
    tinyxml2::XMLDocument svg_data;
    svg_data.LoadFile("resources/maison.svg");
    tinyxml2::XMLElement* e = svg_data.RootElement()->FirstChildElement();
    this->getElementByName(svg_data, "sol", e);
    /* for(int i = 0; i < messages.size(); i++){
        tinyxml2::XMLDocument svg_data;
        tinyxml2::XMLPrinter printer;

        svg_data.LoadFile("resources/maison.svg");

        tinyxml2::XMLElement *rectangle = svg_data.FirstChildElement("svg")->FirstChildElement("g")->FirstChildElement("rect");
        
        //rectangle->SetAttribute("style", "fill:#424242");
        rectangle->SetAttribute("fill", "red");
        svg_data.Print(&printer);
        svg_handle = rsvg_handle_new_from_data ((const unsigned char*) printer.CStr(), printer.CStrSize()-1, NULL);

        rsvg_handle_render_cairo(svg_handle, cr);
        messages.at(i)
    }*/
}

const tinyxml2::XMLElement* Window::getElementByName(tinyxml2::XMLDocument const& document, std::string const& name, tinyxml2::XMLElement* const e){
    std::cout << e->Name() << std::endl;
    if(e != NULL && std::string(e->Name()).compare(name) == 0){
        return e;
    }else{
        if(e->FirstChildElement() != NULL){
            const tinyxml2::XMLElement* children = this->getElementByName(document, name, e->FirstChildElement());
            if(children != NULL){
                return children;
            }
        }
        if(e->NextSiblingElement() != NULL){
            const tinyxml2::XMLElement* siblings = this->getElementByName(document, name, e->NextSiblingElement());
            if(siblings != NULL){
                return siblings;
            }
        }
    }
    return NULL;
}