#include <iostream>
#include <gtk/gtk.h>

#include "../include/functions.hpp"

static gboolean on_changed_event(GtkWidget *widget, gpointer param){
    
    GtkComboBoxText* comboBox = GTK_COMBO_BOX_TEXT(widget);
    
    return FALSE;
}

static gboolean on_clicked_event(GtkWidget *widget, gpointer param){
    std::pair<GtkBuilder**, functions*>* data = (std::pair<GtkBuilder**, functions*>*)param;
    GtkBuilder* builder = *data->first;
    functions* dataModel = data->second;
    GtkEntry* valeurEntry = GTK_ENTRY(gtk_builder_get_object (builder, "valeur"));
    GtkListBox* listBox = GTK_LIST_BOX(gtk_builder_get_object (builder, "listBox"));
    GtkComboBoxText* comboBox = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "comboBox"));
    
    const char* attribut = gtk_combo_box_text_get_active_text(comboBox);
    const char* valeur = gtk_entry_get_text(valeurEntry);

    if(std::string(valeur).size() > 0){
        GtkWidget* newEntry = gtk_label_new(std::string(attribut).append(" : ").append(valeur).c_str());

        gtk_list_box_insert(listBox, newEntry, 0);

        dataModel->insertInData(std::string(attribut), std::string(valeur));
        
        gtk_entry_set_text(valeurEntry, "");

        GtkButton* boutonEnvoyer = GTK_BUTTON(gtk_builder_get_object(builder, "boutonEnvoyer"));
        gtk_widget_set_sensitive (GTK_WIDGET(boutonEnvoyer), TRUE);

        gtk_widget_show_all(GTK_WIDGET(listBox));
    }

    return FALSE;
}

static gboolean on_key_delete_event(GtkWidget *widget, GdkEventKey *event, gpointer param){
    if(event->type == GDK_KEY_RELEASE && event->keyval == GDK_KEY_Delete){
        std::pair<GtkBuilder**, functions*>* data = (std::pair<GtkBuilder**, functions*>*)param;
        GtkBuilder* builder = *data->first;
        functions* dataModel = data->second;
        GtkListBox* listBox = GTK_LIST_BOX(gtk_builder_get_object (builder, "listBox"));
        GtkButton* boutonSupprimer = GTK_BUTTON(gtk_builder_get_object(builder, "boutonSupprimer"));
        GtkListBoxRow* row = gtk_list_box_get_selected_row(listBox);
        GtkButton* boutonEnvoyer = GTK_BUTTON(gtk_builder_get_object(builder, "boutonEnvoyer"));

        GList* rowChildren = gtk_container_get_children(GTK_CONTAINER(row));

        GtkLabel* entryLabel;

        for(GList* l = rowChildren; l != NULL; l = l->next){
            gpointer element_data = l->data;
            entryLabel = GTK_LABEL(element_data);
        }

        const gchar* label = gtk_label_get_text(entryLabel);

        std::string labelString = std::string(label);

        std::string attribut = labelString.substr(0, labelString.find(":") - 1);

        dataModel->deleteEntry(attribut);
        
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
    std::pair<GtkBuilder**, functions*>* data = (std::pair<GtkBuilder**, functions*>*)param;
    GtkBuilder* builder = *data->first;
    functions* dataModel = data->second;
    GtkListBox* listBox = GTK_LIST_BOX(gtk_builder_get_object (builder, "listBox"));
    GList* listBoxChildren = gtk_container_get_children(GTK_CONTAINER(listBox));

    if(listBoxChildren != 0){
        dataModel->sendData();

        for (GList* l = listBoxChildren; l != NULL; l = l->next){
            gpointer element_data = l->data;

            gtk_widget_destroy(GTK_WIDGET(element_data));
        }
    }

    return FALSE;
}