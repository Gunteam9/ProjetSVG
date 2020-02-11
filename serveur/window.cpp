
#include "window.hpp"

Window::Window(int taille_x, int taille_y, std::string const& titre){
    this->taille_x = taille_x;
    this->taille_y = taille_y;
    this->titre = titre;
}

Window::~Window(){
    
}

static RsvgHandle *svg_handle;

static void do_drawing_svg(cairo_t * cr, RsvgHandle * svg_handle)
{
  rsvg_handle_render_cairo(svg_handle, cr);
}

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, 
    gpointer user_data)
{      
  do_drawing_svg(cr, svg_handle);

  return FALSE;
}


void Window::init(int* argc, char*** argv){
    GtkWidget *darea;

    gtk_init(argc, argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    darea = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(this->window), darea);

    tinyxml2::XMLDocument svg_data;
    svg_data.LoadFile("resources/maison.svg");
    tinyxml2::XMLPrinter printer;
    svg_data.Print(&printer);
    svg_handle = rsvg_handle_new_from_data ((const unsigned char*) printer.CStr(), printer.CStrSize()-1, NULL);
    
    
    g_signal_connect(G_OBJECT(darea), "draw", 
        G_CALLBACK(on_draw_event), NULL);
    g_signal_connect(window, "destroy",
        G_CALLBACK(gtk_main_quit), NULL);

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