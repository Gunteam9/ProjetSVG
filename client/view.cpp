//
// Created by gunteam on 05/03/2020.
//

#include <gtk/gtk.h>
#include "include/view.hpp"

using namespace std;

void view::init(int* argc, char*** argv) {

    if (this->width == 0) {
        throw  initializeWindowException("Veuillez préciser la longueur de la fenètre avec la méthode setWidth(int).");
    }

    if (this->height == 0) {
        throw  initializeWindowException("Veuillez préciser le titre de la fenètre avec la méthode setTitre(std::string).");
    }

    if (this->titre.length() == 0) {
        throw  initializeWindowException("Veuillez préciser le titre de la fenètre avec la méthode setTitre(std::string).");
    }

    gtk_init(argc, argv);

    this->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    this->darea = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(view::window), this->darea);



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

void view::init() {

}


void view::setWidth(int width) {
    this->width = width;
}

void view::setHeight(int height) {
    this->height = height;
}

void view::setTitre(std::string titre) {
    this->titre = titre;
}

view view::getInstance() {
    static view v;
    return v;
}

