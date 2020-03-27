//
// Created by gunteam on 21/03/2020.
//

#include "include/client_console.hpp"

using namespace std;

/**
 * Main function
 */
void ClientConsole::start() {

    if (this->func.getDrivensItems().empty())
        throw udpReceiveException("Aucun message n'a été reçu du serveur");

    showDrivenItems();

    string item = selectItemToModify();
    string value = modifyItem(item);

    this->func.insertInData(item, value);

    finish();
}


/**
 * Print drivenItem
 *
 */
void ClientConsole::showDrivenItems() {

    //Affichage des éléments modifiables
    for (auto &item : this->func.getDrivensItems()) {
        cout << item << endl;
    }
}

/**
 * User item selection
 * @return user's choice
 */
string ClientConsole::selectItemToModify() {

    //Choix de l'item à modifier
    string choice;
    do {
        cout << "Entrez le nom de l'item a modifier" << endl;
        getline(cin, choice);
    } while (!this->func.isItemExist(this->func.getDrivensItems(), choice));

    return choice;
}

/**
 * Assign a new value to the specified item
 * @param item
 * @return the new Value
 */
string ClientConsole::modifyItem(const string& item){
    string newValue;
    bool resp = true;

    //Si l'item est un élément de style
    if (this->func.isStyleItem(item)) {

        vector<string> styleElement = this->func.getStyleElements(item);

        //Si l'élément de style contient des règles CSS
        if (!styleElement.empty()) {

            //Si on souhaite modifier plusieurs règles CSS
            while (resp) {
                cout << "Liste des éléments CSS modifiables: " << endl;

                    //Liste les éléments CSS modifiables pour l'item concerné
                    for (auto & it : styleElement) {
                        cout << it << endl;
                    }

                    //Choix de l'utilisateur
                    string choice;
                    do {
                        cout << "Entrez le nom de la règle CSS a modifier" << endl;
                        getline(cin, choice);
                    } while (!this->func.isItemExist(styleElement, choice));

                    //Si l'item a déjà été modifié dans la même session, on supprime l'ancienne valeur et concerve la nouvelle
                    if (newValue.find(choice) != string::npos) {
                        newValue.erase(newValue.find(choice), newValue.find(";", newValue.find(choice)) + 2);
                    }

                    //Ré invoque la fonction pour considérer l'élément CSS comme un item classique
                    // + Mise en forme pour la map pour le serveur
                    newValue += choice + ": " + modifyItem(choice) + "; ";

                    resp = this->func.yesNoQuestion("Voulez vous modifier d'autres règles CSS ? (yes / no)");

            }
        } else {
            cout << "Cet élément driven ne contient pas de règle de style" << endl;
            newValue = "";
        }

    //Pour les item simple
    } else {
        do {
            cout << "Entrez la nouvelle valeur pour l'objet " << item << endl;
            getline(cin, newValue);
        } while (newValue.empty());
    }

    return newValue;
}

/**
 * Finish interaction ... or not
 * If no, return to the start
 */
void ClientConsole::finish() {
    //Demande à l'utilisateur si il souhaite en modifier d'autres
    //Sinon, envoie les données au serveur (puis le client se ferme)
    bool resp = this->func.yesNoQuestion("Voulez vous modifier d'autres item ? (yes / no)");
    if (resp)
        start();
    else
        this->func.sendData();
}


