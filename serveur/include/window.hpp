#pragma once

#include <cairo.h>
#include <gtk/gtk.h>
#include <gio/gfile.h>
#include <librsvg/rsvg.h>
#include <stdlib.h>
#include <string>
#include <tinyxml2.h>
#include <vector>

#include "message.hpp"

/**
 * @brief Namespace où l'on stocke les constantes de ressources.
 * 
 */
namespace constantes {
  constexpr const char* RES_DIR = "serveur/resources/";
}

/**
 * @brief La classe Window va gérer l'affichage du fichier SVG ainsi que la modification dynamique de celui-ci.
 * 
 */
class Window {
    private:
        /**
         * @brief Longueur de la fenêtre.
         * 
         */
        int taille_x;
        /**
         * @brief Largeur de la fenêtre.
         * 
         */
        int taille_y;

        /**
         * @brief Titre de la fenêtre.
         * 
         */
        std::string titre;

        /**
         * @brief Icône de la fenêtre.
         * 
         */
        GdkPixbuf* icon;
        GtkWidget* window;

        /**
         * @brief Cet objet de type RsvgHandle va traduire les informations stockées dynamiquement pour pouvoir les utiliser avec cairo.
         * 
         */
        RsvgHandle *svg_handle;

        /**
         * @brief Cet objet de type XMLDocument va contenir les informations dynamiquement modifiées du fichier SVG.
         * 
         */
        tinyxml2::XMLDocument svg_data;
        GtkWidget* darea;

        Window();
        
    public:
        static Window& getInstance();
        ~Window();
        
        void init(int*, char***, const char*);

        void start();
        void stop();


        /**
         * @brief Cette fonction permet d'obtenir un pointeur vers un élément XMLElement du fichier SVG grâce au nom passé en paramètre.
         * 
         * @return tinyxml2::XMLElement* l'élément correspondant au name donné.
         */
        tinyxml2::XMLElement* getElementByName(std::vector<tinyxml2::XMLElement*>, std::string const&);
        
        /**
         * @brief Cette fonction permet d'obtenir un pointeur vers un élément XMLElement du fichier SVG grâce au label passé en paramètre.
         * 
         * @return tinyxml2::XMLElement* l'élément correspondant au name donné.
         */
        tinyxml2::XMLElement* getAttributeByLabel(const char*, tinyxml2::XMLElement*);

        /**
         * @brief Cette fonction permet d'obtenir les noms des drivens du fichier SVG, soit la valeur de l'attribut by pour chaque balise driven.
         * 
         * @return std::vector<const char*> le vecteur contenant les différents noms.
         */
        const std::vector<const char*> getDrivensName();

        /**
         * @brief Cette fonction nous permet d'obtenir les valeurs actuelles des différents attributs visés par les balises driven.
         * 
         * @return const std::map<const char*, const char*> une map avec comme signature <Attribut, Valeur>.
         */
        const std::map<const char*, const char*> getDrivensValue();
        
        /**
         * @brief Cette fonction nous permet d'obtenir un vecteur de pointeur vers des objets XMLElement représentant des balises driven dans le
         * fichier SVG.
         * 
         * @return const std::vector<tinyxml2::XMLElement*> le vecteur de pointeur vers les drivens. 
         */
        const std::vector<tinyxml2::XMLElement*> getDrivens(tinyxml2::XMLDocument const&, tinyxml2::XMLElement* const);
        
        /**
         * @brief Cette fonction va s'occuper de la mise à jour du fichier SVG et du raffraichissement de la fenêtre GTK.
         * Elle prend en paramètre un vecteur de Message qui va être consommé et traité afin d'être afficher. 
         * 
         */
        void update(std::vector<Message> const&);

        //SETTERS
        void setWidth(int);
        void setHeight(int);
        void setTitre(std::string);


        // GETTERS
        RsvgHandle* getSvgHandle();
        tinyxml2::XMLDocument* getSvgData();
        GtkWidget* getDarea();
        GtkWidget* getWindow();

};