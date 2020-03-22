#include <iostream>

#include <gtk/gtk.h>
#include "gtk_wrappers.cpp"
#include "../include/functions.hpp"

#include "client_graphique.hpp"

ClientGraphique::ClientGraphique(int* argc, char*** argv){
    this->argc = argc;
    this->argv = argv;
}

ClientGraphique::~ClientGraphique(){
    
}

void ClientGraphique::start(){

    GtkWidget *fenetre_principale = NULL;
    GtkBuilder *builder = NULL;
    GError *error = NULL;
    gchar *filename = NULL;

    /* Initialisation de la librairie Gtk. */
    gtk_init(this->argc, this->argv);

    /* Ouverture du fichier Glade de la fenêtre principale */
    builder = gtk_builder_new();

    /* Création du chemin complet pour accéder au fichier test.glade. */
    /* g_build_filename(); construit le chemin complet en fonction du système */
    /* d'exploitation. ( / pour Linux et \ pour Windows) */
    filename =  g_build_filename ("client/test_gtk/client_xml.glade", NULL);

    /* Chargement du fichier test.glade. */
    gtk_builder_add_from_file(builder, filename, &error);
    g_free(filename);
    if (error){
        gint code = error->code;
        g_printerr("%s\n", error->message);
        g_error_free (error);
        exit(code);
    }

    /* Récupération du pointeur de la fenêtre principale */
    fenetre_principale = GTK_WIDGET(gtk_builder_get_object (builder, "MainWindow"));

    /* Affectation du signal "destroy" à la fonction gtk_main_quit(); pour la */
    /* fermeture de la fenêtre. */
    g_signal_connect (G_OBJECT (fenetre_principale), "destroy", (GCallback)gtk_main_quit, NULL);

    gtk_window_set_position(GTK_WINDOW(fenetre_principale), GTK_WIN_POS_CENTER);

    GtkComboBoxText* comboBox = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "comboBox"));
    GtkButton* boutonAjouter = GTK_BUTTON(gtk_builder_get_object(builder, "ajouter"));
    GtkListBox* listBox = GTK_LIST_BOX(gtk_builder_get_object(builder, "listBox"));
    GtkButton* boutonSupprimer = GTK_BUTTON(gtk_builder_get_object(builder, "boutonSupprimer"));
    GtkButton* boutonEnvoyer = GTK_BUTTON(gtk_builder_get_object(builder, "boutonEnvoyer"));

    gtk_widget_set_sensitive (GTK_WIDGET(boutonSupprimer), FALSE);
    gtk_widget_set_sensitive (GTK_WIDGET(boutonEnvoyer), FALSE);

    functions f;

    std::vector<std::string> drivensItems = f.getDrivensItems();

    for(unsigned int i = 1; i < drivensItems.size(); i++){
        gtk_combo_box_text_insert_text(comboBox, i, drivensItems[i].c_str());  
    }
    GtkEntry* input = GTK_ENTRY(gtk_builder_get_object (builder, "valeur"));

    std::pair<GtkBuilder**, functions*> inputData;
    inputData.first = &builder;
    inputData.second = &f;

    gtk_combo_box_set_active(GTK_COMBO_BOX(comboBox), 0);

    g_signal_connect (G_OBJECT (comboBox), "changed", (GCallback)on_changed_event, NULL);

    g_signal_connect (G_OBJECT (boutonAjouter), "clicked", (GCallback)on_clicked_event, (gpointer)&inputData);

    g_signal_connect (G_OBJECT (boutonSupprimer), "clicked", (GCallback)on_delete_event, (gpointer)&inputData);

    g_signal_connect (G_OBJECT (boutonEnvoyer), "clicked", (GCallback)on_send_event, (gpointer)&inputData);

    g_signal_connect (G_OBJECT (listBox), "key-release-event", (GCallback)on_key_delete_event, (gpointer)&inputData);

    g_signal_connect (G_OBJECT (listBox), "row-selected", (GCallback)on_row_selected, (gpointer)boutonSupprimer);

    /* Affichage de la fenêtre principale. */
    gtk_widget_show_all (fenetre_principale);

    gtk_main();
}