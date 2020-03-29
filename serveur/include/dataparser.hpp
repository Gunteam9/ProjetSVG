//
// Created by ionas on 10/02/2020.
//

#pragma once

#include <map>
#include <stdlib.h>

#include "../../vendor/cbor11/cbor11.hpp"
#include "../../vendor/exceptions/errorException.hpp"
#include "message.hpp"
#include "window.hpp"

/**
 * @brief Cette map associe un mot clé couleur à une valeur héxadécimale. 
 * 
 */
static std::map<std::string, std::string> COULEURS_MAP;

class DataParser {
    private:
        /**
         * L'attribut les nécessaire pour éviter de devoir lier la window avec le client
         */
        std::map<const char *,const  char*> lesElementsDriven;

        /**
         * @brief Instance de la classe DataParser, c'est un singleton.
         * 
         */
        static DataParser instance;

        /**
         * @brief Cette map associe un type d'attribut SVG à une fonction d'interpolation.
         * Cette fonction prend en paramètre la valeur actuelle, la nouvelle valeur ainsi que le nombre 
         * de pas à effectuer pour passer de l'ancienne à la nouvelle valeur.
         * 
         */
        std::map<std::string, std::vector<std::string>(*)(std::string, std::string, double)> interpolationMap;

    public:
        DataParser();

        /**
         * @brief Initialisation de la map de couleurs.
         * 
         */
        void initColorMap();


        //Getter
        const map<const char *, const char *> &getLesElementsDriven() const;
        static DataParser& getInstance();

        //Setter
        void setLesElementsDriven(const map<const char *, const char *> &lesElementsDriven);

        /**
         * @brief Méthode qui prend un cbor::map encodé et qui renvoie un vector de messages contenant les noms et les
         * nouvelles valeur des attributs a modifier
         * 
         * @return vector<Message> 
         */
        vector<Message> lireMessage(cbor::binary);

        /**
         * @brief Cette fonction valide en fonction d'un type d'attribut ainsi que la valeur à tester, l'interpolation ou non.
         * Elle va appliquer la regex du type d'attribut à la valeur et décider ou non si le message sera traité ou non.
         * 
         * @return true si la valeur est éligible au traitement
         * @return false si la valeur n'est pas éligible au traitement
         */
        bool validateValue(const char*, const char*);

        /**
         * @brief Cette fonction effectue l'interpolation en fonction de la première valeur et la dernière valeur par
         * 
         * @return std::vector<std::string> un vecteur contenant toutes les valeurs comprises entre l'ancienne et la nouvelle.
         */
        std::vector<std::string> interpolate(std::string, std::string, std::string, double);

        /**
         * @brief Méthode qui retourne une map contenant en clé les nom des attributs de type style et en valeur un
         * vector contenant les noms des attributs styles
         */
        cbor::map getCss();

        /**
         * @brief Méthode qui retourne une map contenant en clé les nom des attributs de type style et en valeur
         * une une map contenant en clé le nom des éléments style et en valeur leur valeur actuelles.
         * @return
         */
        std::map<string,std::map<string,string>> getCssValues();
};

