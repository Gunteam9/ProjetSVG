//
// Created by ionas on 10/02/2020.
//
#include <fstream>
#include <regex>
#include <math.h>
#include "../vendor/color/src/color/color.hpp"

#include "include/dataparser.hpp"

std::vector<double> rgbToHsv(float r, float g, float b){
    color::hsv<float> hsvT({0, 0, 100});
    color::rgb<float> rgbTest({r/255, g/255, b/255});
    hsvT = rgbTest;
    return std::vector<double>({hsvT[0], hsvT[1], hsvT[2]});
}

double normAngle(double a){
    a =  std::fmod(a, 360);
    a += (a < 0) ? 360 : 0;
    return a;
}

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

std::vector<std::string> numberInterpolation(std::string oldValue, std::string newValue, double steps){
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

std::vector<std::string> styleInterpolation(std::string oldRule, std::string newRule, double steps){
    std::vector<std::string> values;

    std::string oldRuleValue = oldRule.substr(oldRule.find(":") + 2, oldRule.size() - (oldRule.substr(0, oldRule.find(":")).size()) - 4);
    std::string newRuleValue = newRule.substr(newRule.find(":") + 2, newRule.size() - (newRule.substr(0, newRule.find(":")).size()) - 4);

    std::cout << oldRuleValue << std::endl;
    std::cout << newRuleValue << std::endl;

    return values;
}   

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

DataParser DataParser::getInstance(){
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

        Message m(element,valeur);
        mesMessages.push_back(m);
        it++;
    }

    return mesMessages;
}

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

std::vector<std::string> DataParser::interpolate(std::string type, std::string oldValue, std::string newValue, double steps){
    return this->interpolationMap[type](oldValue, newValue, steps);
}

/** pour le transformer en map normale
 *   cbor::map m = d.getCss();
  std::map<cbor,cbor> m1 = m ;
  std::string s1 = m1.begin()->first;
  std::vector<cbor> v = m1.begin()->second ;
  std::string premiere_value = v[0];

 * @return
 */
cbor::map DataParser::getCss() {
    Window & w = Window::getInstance();
    std::map<const char *,const  char*> driven= w.getDrivensValue();
    std::map<const char *,const  char*>::iterator it ;

    cbor::map map;

    for(it = driven.begin(); it != driven.end();++it){
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




