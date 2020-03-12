//
// Created by gunteam on 05/03/2020.
//


#pragma once

#include <iostream>
#include <string>
#include "../../vendor/exceptions/initializeWindowException.hpp"


class view {
public:
    static view getInstance();

    void setWidth(int);
    void setHeight(int);
    void setTitre(std::string);

    void init(int* argc, char*** argv);

private:
    int width;
    int height;
    std::string titre;

    GtkWidget* window;
    GtkWidget* darea;



};



