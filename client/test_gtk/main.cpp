#include <iostream>

#include <gtk/gtk.h>

static gboolean on_changed_event(GtkWidget *widget, gpointer param){
    
    GtkComboBoxText* comboBox = GTK_COMBO_BOX_TEXT(widget);

    //std::cout << gtk_combo_box_text_get_active_text(comboBox) << std::endl;

    return FALSE;
}

static gboolean on_clicked_event(GtkWidget *widget, gpointer param){
    GtkBuilder* builder = (GtkBuilder*) param;
    GtkEntry* valeurEntry = GTK_ENTRY(gtk_builder_get_object (builder, "valeur"));
    GtkListBox* listBox = GTK_LIST_BOX(gtk_builder_get_object (builder, "listBox"));
    GtkComboBoxText* comboBox = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "comboBox"));
    
    const char* attribut = gtk_combo_box_text_get_active_text(comboBox);
    const char* valeur = gtk_entry_get_text(valeurEntry);

    if(std::string(valeur).size() > 0){
        GtkWidget* newEntry = gtk_label_new(std::string(attribut).append(" : ").append(valeur).c_str());

        gtk_list_box_insert(listBox, newEntry, 0);

        gtk_entry_set_text(valeurEntry, "");

        GtkButton* boutonEnvoyer = GTK_BUTTON(gtk_builder_get_object(builder, "boutonEnvoyer"));
        gtk_widget_set_sensitive (GTK_WIDGET(boutonEnvoyer), TRUE);

        gtk_widget_show_all(GTK_WIDGET(listBox));
    }

    return FALSE;
}

static gboolean on_key_delete_event(GtkWidget *widget, GdkEventKey *event, gpointer param){
    if(event->type == GDK_KEY_RELEASE && event->keyval == GDK_KEY_Delete){
        GtkBuilder* builder = (GtkBuilder*)param;
        GtkListBox* listBox = GTK_LIST_BOX(gtk_builder_get_object (builder, "listBox"));
        GtkButton* boutonSupprimer = GTK_BUTTON(gtk_builder_get_object(builder, "boutonSupprimer"));
        GtkListBoxRow* row = gtk_list_box_get_selected_row(listBox);
        GtkButton* boutonEnvoyer = GTK_BUTTON(gtk_builder_get_object(builder, "boutonEnvoyer"));
        
        gtk_widget_destroy(GTK_WIDGET(row));

        GList* listBoxChildren = gtk_container_get_children(GTK_CONTAINER(listBox));
        if(listBoxChildren == 0){
            gtk_widget_set_sensitive (GTK_WIDGET(boutonEnvoyer), FALSE);
        }

        gtk_widget_set_sensitive (GTK_WIDGET(boutonSupprimer), FALSE);
    }

    return FALSE;
}


static gboolean on_delete_event(GtkWidget *widget, gpointer param){
    GtkBuilder* builder = (GtkBuilder*)param;
    GtkListBox* listBox = GTK_LIST_BOX(gtk_builder_get_object (builder, "listBox"));
    GtkButton* boutonSupprimer = GTK_BUTTON(gtk_builder_get_object(builder, "boutonSupprimer"));
    GtkListBoxRow* row = gtk_list_box_get_selected_row(listBox);
    GtkButton* boutonEnvoyer = GTK_BUTTON(gtk_builder_get_object(builder, "boutonEnvoyer"));

    gtk_widget_destroy(GTK_WIDGET(row));
    
    GList* listBoxChildren = gtk_container_get_children(GTK_CONTAINER(listBox));
    
    if(listBoxChildren == 0){
        gtk_widget_set_sensitive (GTK_WIDGET(boutonEnvoyer), FALSE);
    }

    gtk_widget_set_sensitive (GTK_WIDGET(boutonSupprimer), FALSE);

    return FALSE;
}

static gboolean on_row_selected(GtkWidget *widget,  GtkListBoxRow *row, gpointer param){

    GtkWidget* bouton = (GtkWidget*)param;

    gtk_widget_set_sensitive (bouton, TRUE);

    return FALSE;
}


static gboolean on_send_event(GtkWidget *widget, gpointer param){

    GtkListBox* listBox = (GtkListBox*)param;

    GList* listBoxChildren = gtk_container_get_children(GTK_CONTAINER(listBox));

    if(listBoxChildren != 0){

    }

    return FALSE;
}

int main(int argc, char* argv[]){

    std::cout << "Hello World" << std::endl;

    GtkWidget *fenetre_principale = NULL;
    GtkBuilder *builder = NULL;
    GError *error = NULL;
    gchar *filename = NULL;

    /* Initialisation de la librairie Gtk. */
    gtk_init(&argc, &argv);

    /* Ouverture du fichier Glade de la fenêtre principale */
    builder = gtk_builder_new();

    /* Création du chemin complet pour accéder au fichier test.glade. */
    /* g_build_filename(); construit le chemin complet en fonction du système */
    /* d'exploitation. ( / pour Linux et \ pour Windows) */
    filename =  g_build_filename ("client_xml.glade", NULL);

    /* Chargement du fichier test.glade. */
    gtk_builder_add_from_file(builder, filename, &error);
    g_free(filename);
    if (error){
        gint code = error->code;
        g_printerr("%s\n", error->message);
        g_error_free (error);
        return code;
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

    gtk_combo_box_text_insert_text(comboBox, 0, "sun_x");
    gtk_combo_box_text_insert_text(comboBox, 1, "sun_y");
    gtk_combo_box_text_insert_text(comboBox, 2, "sun_style");
    gtk_combo_box_text_insert_text(comboBox, 3, "sun_fill");

    gtk_combo_box_set_active(GTK_COMBO_BOX(comboBox), 0);

    g_signal_connect (G_OBJECT (comboBox), "changed", (GCallback)on_changed_event, NULL);

    g_signal_connect (G_OBJECT (boutonAjouter), "clicked", (GCallback)on_clicked_event, (gpointer)builder);

    g_signal_connect (G_OBJECT (boutonSupprimer), "clicked", (GCallback)on_delete_event, (gpointer)builder);

    g_signal_connect (G_OBJECT (boutonEnvoyer), "clicked", (GCallback)on_send_event, (gpointer)listBox);

    g_signal_connect (G_OBJECT (listBox), "key-release-event", (GCallback)on_key_delete_event, (gpointer)builder);

    g_signal_connect (G_OBJECT (listBox), "row-selected", (GCallback)on_row_selected, (gpointer)boutonSupprimer);

    /* Affichage de la fenêtre principale. */
    gtk_widget_show_all (fenetre_principale);

    gtk_main();

    return 0;
}