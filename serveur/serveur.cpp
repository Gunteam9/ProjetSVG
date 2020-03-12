//
// Created by ionas on 11/02/2020.
//

#include "include/serveur.hpp"

#include "../vendor/exceptions/udpSendingException.hpp"

using namespace std;

Serveur::Serveur(char * IMAGE_SVG) {

    this->IMAGE_SVG=IMAGE_SVG;


    //Addresse IP
    struct sockaddr_in address;


    // Création de la socket
    if ((this->sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        throw udpRuntimeException(IP_SERVER, PORT);
    }

    // Initialisation de la socket
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(IP_SERVER);
    address.sin_port = htons(PORT);

    // Binding
    if (bind(sock, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        throw udpBindsException();
    }

}


Serveur::~Serveur() {

}


void Serveur::startServer(Window& w) {
    while (true) {
        char buffer[1024] = {0};


        sockaddr_in from;
        socklen_t fromlen = sizeof(from);


        if (recvfrom(sock, buffer, sizeof(buffer), 0, reinterpret_cast<sockaddr *>(&from), &fromlen) < 0) {
            throw udpReceiveException();
        }


        std::vector<unsigned char> encodedMessge;

        int taille = strlen(buffer);

        //on reserve la place dans le vector,
        encodedMessge.reserve(taille);


        // on assigne les valeurs du buffer dans le vector
        for (int i = 0; i < taille; ++i) {
            encodedMessge.push_back(buffer[i]);
        }


        cbor::binary binaryEncodedMessage = encodedMessge;

        DataParser p = DataParser::getInstance();

        std::vector<Message> vT = p.lireMessage(binaryEncodedMessage);

        if (vT[0].getNomElement() == "?") { //si le message reçu commence par un '?' alors on envoie les driven au client
            this->envoiDesAttributs(w,from);
            this->envoiDuCss(w,from);
        } else {

            w.update(vT);
        }
    }

}

int Serveur::getMaSocket() const{
    return this->sock;
}

void Serveur::envoiDesAttributs(Window& w,sockaddr_in from) {

    vector<const char *> lesElementsDriven = w.getDrivensName();

    std::string s ="Les elements driven sont : \n";
    for(const char* elemnt : lesElementsDriven  ){
        s.append(elemnt).append("\n");
    }

    const char * drivenImage = s.c_str();



    int resEnvoi = sendto(sock, (char *)drivenImage, strlen(drivenImage), 0, reinterpret_cast<const sockaddr *>(&from),sizeof(from));
    if (resEnvoi < 0) {
        throw udpSendingException();
    }

}

void Serveur::envoiDuCss(Window &w, sockaddr_in from) {
    DataParser dp = DataParser::getInstance();

    cbor::map map = dp.getCss();

    std::string s ="Les elements de type style sont : \n";

    cbor::map::iterator it ;
    for(it=map.begin(); it!=map.end();++it){
        cbor::string first =  it->first;
        s.append(first + ": ");
        cbor::array ar = it->second;
        for(cbor::string second : ar ){
            s.append(second + " ");
        }
        s.append("\n");

    }

    std::cout<<s<<std::endl;

    const char * drivenImage = s.c_str();

    int resEnvoi = sendto(sock, (char *)drivenImage, strlen(drivenImage), 0, reinterpret_cast<const sockaddr *>(&from),sizeof(from));
    if (resEnvoi < 0) {
        throw udpSendingException();
    }

}



