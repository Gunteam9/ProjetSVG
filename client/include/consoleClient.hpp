//
// Created by gunteam on 21/03/2020.
//


#pragma once

#include <string>
#include <iostream>
#include "functions.hpp"

#include "iClient.hpp"

class consoleClient : iClient {
public:
    void start() override;

private:
    //Instencie le modèle
    functions func;

    void showDrivenItems();
    string selectItemToModify();
    string modifyItem(const std::string& item);
    void finish();

};



