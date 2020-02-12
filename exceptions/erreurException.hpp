//
// Created by ionas on 10/02/2020
//
#pragma once

#include <exception>
#include <string>

using namespace std;

class Erreur: public exception
{

private:
    string m_phrase;            //Description de l'exceptions

public:
    Erreur(string const& phrase) throw();

    virtual ~Erreur() throw(){}

    virtual const char* what() const throw();

};