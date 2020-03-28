//
// Created by ionas on 10/02/2020.
//
#include <fstream>
#include <regex>
#include <math.h>
#include "../vendor/color/src/color/color.hpp"

#include "include/dataparser.hpp"

/**
 * @brief Cette fonction nous donne des valeurs HSV grâce aux paramètres donnés correspondants respectivement à des valeur RGB.
 * 
 * @param r composante rouge
 * @param g composante verte
 * @param b composante bleue
 * @return std::vector<double> le vecteur contenant les valeurs HSV. 
 */
std::vector<double> rgbToHsv(float r, float g, float b){
    color::hsv<float> hsvT({0, 0, 100});
    color::rgb<float> rgbTest({r/255, g/255, b/255});
    hsvT = rgbTest;
    return std::vector<double>({hsvT[0], hsvT[1], hsvT[2]});
}

/**
 * @brief Cette fonction nous permet de normaliser un angle qui sera utiliser pour obtenir une position dans la palette de couleur.
 * 
 * @param a un angle en degré
 * @return double l'angle normalisé
 */
double normAngle(double a){
    a =  std::fmod(a, 360);
    a += (a < 0) ? 360 : 0;
    return a;
}

/**
 * @brief Cette fonction va effectuer l'interpolation de couleur à partir de l'ancienne valeur vers la nouvelle valeur en fonction d'un nombre de pas
 * donné en paramètre. Pour ce faire, on récupère la valeur héxadécimale des deux couleurs. Puis on prend les valeurs HSV de ces dernières.
 * On effectue l'interpolation grâce à une formule. Enfin on repasse la valeur obtenue en RGB, puis on prend la valeur Héxadécimale de cette valeur
 * et on la met dans le vecteur.
 * 
 * @param oldColor l'ancienne couleur
 * @param newColor la nouvelle couleur
 * @param steps le nombre de pas à effectuer
 * @return std::vector<std::string> les valeurs interpolées entre l'ancienne valeur et la nouvelle.
 */
std::vector<std::string> colorInterpolation(std::string oldColor, std::string newColor, double steps){
    std::vector<std::string> values;

    std::string hexOldColor = COULEURS_MAP[oldColor].substr(1, std::string::npos);
    std::string hexNewColor = COULEURS_MAP[newColor].substr(1, std::string::npos);

    double rOld = std::stoi(hexOldColor.substr(0, 2), nullptr, 16);
    double gOld = std::stoi(hexOldColor.substr(2, 2), nullptr, 16);
    double bOld = std::stoi(hexOldColor.substr(4, 2), nullptr, 16);

    int rNew = std::stoi(hexNewColor.substr(0, 2), nullptr, 16);
    int gNew = std::stoi(hexNewColor.substr(2, 2), nullptr, 16);
    int bNew = std::stoi(hexNewColor.substr(4, 2), nullptr, 16);

    std::vector<double> oldHsv = rgbToHsv(rOld, gOld, bOld);
    std::vector<double> newHsv = rgbToHsv(rNew, gNew, bNew);
 
    double h1 = normAngle(oldHsv[0]);
    double h2 = normAngle(newHsv[0]);

    double d = h2 - h1;
    double delta = (d + ((std::abs(d) > 180) ? ((d < 0) ? 360 : -360) : 0)) / (steps + 1.0);

    for(double i = 4; i < steps - 2; i++){
        double t = i/steps;
        double hT = std::fmod(((h1 + (delta * i)) + 360), 360);
        double sT = oldHsv[1] + (t * (newHsv[1] - oldHsv[1]));
        double vT = oldHsv[2] + (t * (newHsv[2] - oldHsv[2]));
        color::hsv<double> hsvT({hT, sT, vT});
        color::rgb<float> rgbT({0, 0, 0});
        rgbT = hsvT;
        std::stringstream ifs;
        int r = rgbT[0] * 255;
        int g = rgbT[1] * 255;
        int b = rgbT[2] * 255;
        ifs << "#" << std::hex << (r << 16 | g << 8 | b);
        values.push_back(ifs.str());
    }

    values.push_back(newColor);
    return values;
}

/**
 * @brief Cette fonction nous permet d'interpoler deux coordonnées. Son fonctionnement est identique à l'interpolation pour les nombres 
 * (voir fonction : numberInterpolation)
 * 
 * @param oldValue l'ancienne valeur
 * @param newValue la nouvelle valeur
 * @param steps le nombre de pas à effectuer.
 * @return std::vector<std::string> le vecteur de valeurs interpolées entre l'ancienne valeur et la nouvelle.
 */
std::vector<std::string> coordinateInterpolation(std::string oldValue, std::string newValue, double steps){
    std::vector<std::string> values;

    std::size_t size = 3;

    float min = std::stod(oldValue, &size);
    float max = std::stod(newValue, &size);

    double t = 1;

    for(double i = 1; i < steps; i++){
        t = i/steps;
        std::stringstream ifs;
        double v = (min + ((max - min) * t));
        ifs << v;
        values.push_back(ifs.str());
    }


    return values;
}

/**
 * @brief Cette fonction nous permet d'interpoler deux nombres. La fonction d'interpolation est une formule assez simple (old + (new - old) * pas), nous l'appliquons juste
 * pour chaque pas et nous mettons la valeur obtenue dans le vecteur.
 * 
 * @param oldValue l'ancienne valeur
 * @param newValue la nouvelle valeur
 * @param steps le nombre de pas 
 * @return std::vector<std::string> le vecteurs contenant les différentes valeurs.
 */
std::vector<std::string> numberInterpolation(std::string oldValue, std::string newValue, double steps){
    std::vector<std::string> values;

    std::size_t size = 3;

    float min = std::stod(oldValue, &size);
    float max = std::stod(newValue, &size);

    std::cout << max << endl;
    std::cout << min << endl;

    double t = 1;

    for(double i = 1; i < steps; i++){
        t = i/steps;
        std::stringstream ifs;
        double v = (min + ((max - min) * t));
        ifs << v;
        values.push_back(ifs.str());
    }

    values.push_back(std::to_string(max));

    return values;
}

/**
 * @brief Nous n'effectuons pas d'interpolation pour les attributs de style.
 * 
 * @param oldRule ancienne règle css
 * @param newRule nouvelle règle css
 * @param steps nombre de pas
 * @return std::vector<std::string> le vecteur contenant les deux valeurs : ancienne, nouvelle. 
 */
std::vector<std::string> styleInterpolation(std::string oldRule, std::string newRule, double steps){
    std::vector<std::string> values;

    values.push_back(oldRule);
    values.push_back(newRule);

    return values;
}   

/**
 * @brief Ici on va initialiser la map de couleur, mais aussi la map qui associe à chaque type d'attribut SVG une fonction d'interpolation.
 * 
 */
DataParser::DataParser(){
    this->initColorMap();
    this->interpolationMap = {
        {"color-keyword", &colorInterpolation},
        {"number", &numberInterpolation},
        {"integer", &numberInterpolation},
        {"opacity-value", &numberInterpolation},
        {"angle", &numberInterpolation},
        {"coordinate", &numberInterpolation},
        {"style", &styleInterpolation}
    };
}

DataParser& DataParser::getInstance(){
    static DataParser i;
    return i;
}

void DataParser::initColorMap(){
    std::ifstream colors("serveur/config/colors.cfg");
    std::string ligne;

    if(colors.is_open()){
        while(getline(colors, ligne)){
            std::string color = ligne.substr(1, ligne.find(":") - 2);
            std::string value = ligne.substr(ligne.find(":") + 3, (ligne.size() - 4) - (ligne.substr(0, ligne.find(":")).size() + 1));
            COULEURS_MAP.insert({color, value});
        }
    }else{
        std::cout << "Impossible d'ouvrir le fichier de configuration" << std::endl;
    }
}

/**
 * Méthode qui prend un cbor encodé, le cbor doit être une map d'élément valeur
 * @param encodedItem est le cbor encodé
 * @return un tableau des messages
 */
vector<Message> DataParser::lireMessage(cbor::binary encodedItem) {
    cbor decodedItem= cbor::decode(encodedItem);

    if(!decodedItem.is_map()){
        throw errorException("EncodedItem doit être une map encodée");
    }

    map<cbor,cbor> maMap = decodedItem;
    vector<Message> mesMessages;
    mesMessages.reserve(maMap.size());
    map<cbor,cbor>::iterator it = maMap.begin();

    while (it != maMap.end()){
        string element = it->first;
        string valeur = it->second;

        if(std::regex_match(element,std::regex(".*_style"))){
            std::string s = valeur;
            std::map<string,string> map1;

            while(s.length()>2) {
                int indicefin = s.find(";");
                std::string couple = s.substr(0, indicefin);
                std::string type = couple.substr(0, couple.find(":")); // changer le couple.find en s.find
                std::string valeur = couple.substr(couple.find(":") + 2, couple.length());

                map1.insert({type, valeur});

                if (indicefin + 2 >= s.length()) {
                    s = "";
                } else {
                    s = s.substr(indicefin + 2, s.length());
                }
            }

            std::map<string,string> present = this->getCssValues().at(element);
            std::map<string,string>::iterator iterator;

            for (iterator=present.begin() ; iterator!=present.end() ; ++iterator) {
                map1.insert({iterator->first,iterator->second});
            }

            string valeurFinale;
            for(iterator=map1.begin(); iterator!=map1.end(); ++iterator){
                valeurFinale.append(iterator->first+": "+iterator->second+"; ");
            }
            valeur=valeurFinale.substr(0,valeurFinale.length()-1);

        }

        Message m(element,valeur);
        mesMessages.push_back(m);
        it++;
    }

    return mesMessages;
}

/**
 * @brief Pour pouvoir valider les valeurs on regarde dans le fichier de type, on prend la regex et on applique celle ci sur la valeur en paramètre.
 * 
 * @param type type de l'attribut svg
 * @param value valeur voulant être appliquée
 * @return true si la regex s'applique
 * @return false sinon
 */
bool DataParser::validateValue(const char* type, const char* value){
    std::ifstream types("serveur/config/types.cfg");
    std::string ligne;
    std::map<std::string, std::string> typesMap;

    if(types.is_open()){
        while(getline(types, ligne)){
            std::string type = ligne.substr(0, ligne.find("="));
            std::string regex = ligne.substr(ligne.find("=") + 1, (ligne.size() - 1) - (ligne.substr(0, ligne.find("=")).size() + 1));
            typesMap.insert({type, regex});
        }
    }else{
        std::cout << "Impossible d'ouvrir le fichier de configuration" << std::endl;
    }

    std::regex r(typesMap[type]);

    bool matching = regex_match(value, r);

    types.close();

    return matching;
}

/**
 * @brief Cette fonction est une fonction assez générique, nous permettant d'appeler la bonne fonction en fonction du type d'attribut
 * donné en paramètre.
 * 
 * @param type type de l'attribut SVG
 * @param oldValue ancienne valeur
 * @param newValue nouvelle valeur
 * @param steps nombre de pas
 * @return std::vector<std::string> les valeurs interpolées. 
 */
std::vector<std::string> DataParser::interpolate(std::string type, std::string oldValue, std::string newValue, double steps){
    return this->interpolationMap[type](oldValue, newValue, steps);
}

cbor::map DataParser::getCss() {
    std::map<const char *,const  char*>::iterator it ;
    cbor::map map;

    for(it = this->lesElementsDriven.begin(); it != this->lesElementsDriven.end();++it){
        if(std::regex_match(it->first, std::regex(".*_style"))){
            cbor::string s = it->second;
            cbor::array vector;

            while(s.length()>2) {
                int indicefin = s.find(";");
                std::string couple = s.substr(0, indicefin);
                cbor::string type =  couple.substr(0,s.find(":"));

                vector.emplace_back(type);

                if(indicefin+2>=s.length()){
                    s="";
                }else {
                    s = s.substr(indicefin + 2, s.length());
                }
            }
            cbor::string first = it->first;
            map.insert({first,vector});
        }
    }
    return map;
}

std::map<string,std::map<string,string>> DataParser::getCssValues() {
    std::map<const char *,const  char*>::iterator it ;

    std::map<string,std::map<string,string>> map;

    for(it = this->lesElementsDriven.begin(); it != this->lesElementsDriven.end();++it){
        if(std::regex_match(it->first, std::regex(".*_style"))){

            cbor::string s = it->second;
            std::map<string,string> map1;

            while(s.length()>2) {
                int indicefin = s.find(";");
                std::string couple = s.substr(0, indicefin);
                std::string type =  couple.substr(0,couple.find(":"));
                std::string valeur = couple.substr(couple.find(":")+2,couple.length());

                map1.insert({type,valeur});

                if(indicefin+2>=s.length()){
                    s="";
                }else {
                    s = s.substr(indicefin + 2, s.length());
                }
            }
            cbor::string first = it->first;
            map.insert({first,map1});
        }
    }
    return map;
}

void DataParser::setLesElementsDriven(const map<const char *, const char *> &lesElementsDriven) {
    DataParser::lesElementsDriven = lesElementsDriven;
}

const map<const char *, const char *> &DataParser::getLesElementsDriven() const {
    return lesElementsDriven;
}




