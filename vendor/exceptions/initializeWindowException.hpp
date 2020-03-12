//
// Created by gunteam on 05/03/2020.
//


#pragma once


#include <string>

class initializeWindowException : public std::exception{

private:
    std::string message;

public:
    initializeWindowException(std::string const& message) throw() {}

    virtual ~initializeWindowException() throw() {}

    virtual const char* what() const throw() {
        return message.c_str();
    }

};



