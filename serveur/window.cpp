
#include <iostream>
#include <chrono>
#include <thread>

#include "include/dataparser.hpp"
#include "include/window.hpp"
#include "gtk_drawing.cpp"

Window::Window(){

}

Window::~Window(){
}

Window& Window::getInstance(){
    static Window w;
    return w;
}

void Window::init(int* argc, char*** argv, const char* svg){

    if(this->taille_x == 0){
        std::cout << "Veuillez préciser la longueur de la fenètre avec la méthode setWidth(int)." << std::endl;
        exit(1);
    }

    if(this->taille_y == 0){
        std::cout << "Veuillez préciser la largeur de la fenètre avec la méthode setHeight(int)." << std::endl;
        exit(1);
    }

    if(this->titre.length() == 0){
        std::cout << "Veuillez préciser le titre de la fenètre avec la méthode setTitre(std::string)." << std::endl;
        exit(1);
    }

    if(*argc == 1){
        std::cout << "Veuillez préciser le nom du fichier svg, il doit se trouver dans le dossier serveur/resources." << std::endl;
        exit(1);
    }

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

    this->icon = gdk_pixbuf_new_from_file(chemin.c_str(), NULL);

    gtk_window_set_icon(GTK_WINDOW(this->window), this->icon);
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

const std::vector<const char*> Window::getDrivensName(){
    tinyxml2::XMLElement *root = Window::svg_data.RootElement();

    std::vector<tinyxml2::XMLElement*> drivens = getDrivens(svg_data, root);

    std::vector<const char*>  drivensName;

    for(tinyxml2::XMLElement* driven : drivens){
        drivensName.push_back(driven->Attribute("by"));
    }
    return drivensName;
}

const std::map<const char*, const char*> Window::getDrivensValue(){
    tinyxml2::XMLElement *root = Window::svg_data.RootElement();

    std::vector<tinyxml2::XMLElement*> drivens = getDrivens(svg_data, root);

    std::map<const char*, const char*> drivensCurrentValue;

    for(tinyxml2::XMLElement* driven : drivens){
        tinyxml2::XMLElement* attribut = driven->Parent()->ToElement();
        const char* target = driven->Attribute("target");
        drivensCurrentValue.insert(std::make_pair(driven->Attribute("by"), attribut->Attribute(target)));
    }

    return drivensCurrentValue;
}

tinyxml2::XMLElement* Window::getAttributeByLabel(const char* label, tinyxml2::XMLElement* currentElement){
    if(currentElement != NULL){
        if(std::string(currentElement->Name()).compare(std::string(label)) == 0){
            return currentElement;
        }else{
            return this->getAttributeByLabel(label, currentElement->NextSiblingElement());
        }
    }

    return NULL;
}

void Window::update(std::vector<Message> const& v){
    std::cout << "Nouveau message pour la window" << std::endl;

    tinyxml2::XMLElement *root = this->svg_data.RootElement();

    std::vector<tinyxml2::XMLElement*> drivens = this->getDrivens(this->svg_data, root);
    std::vector<const char*> drivensName = getDrivensName();

    for(Message m : v){
        tinyxml2::XMLElement* attribut = getElementByName(drivens, m.getNomElement());
        const char* nomAttribut = attribut->Attribute("target");
        const char* typeAttribut = attribut->Attribute("type");
        tinyxml2::XMLElement* parent = attribut->Parent()->ToElement();
        bool matchingValue = DataParser::getInstance().validateValue(typeAttribut, m.getValeur().c_str());
        if(matchingValue){
            std::vector<std::string> values = DataParser::getInstance().interpolate(typeAttribut, parent->Attribute(nomAttribut), m.getValeur().c_str());
            std::vector<Message> messages;
            for(std::string s : values){
                parent->SetAttribute(nomAttribut, s.c_str());
                gtk_widget_queue_draw(Window::darea);
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }else{
            std::cout << "Parametre pas conforme" << std::endl;
        }
        //DataParser::validateValue(typeAttribut, m.getValeur().c_str());

    }
    
}

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