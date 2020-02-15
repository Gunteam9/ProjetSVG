//
// Created by ionas on 10/02/2020
//
#pragma once

#include <exception>
#include <string>

using namespace std;

class ErreurException: public std::exception
{

private:
    string m_phrase;            //Description de l'exceptions

public:
    ErreurException(string const& phrase) throw();

    virtual ~ErreurException() throw(){}

    virtual const char* what() const throw();

};