//
// Created by ionas on 10/02/2020
// Edited by romain on 17/02/2020
//

#pragma once
#include <iostream>

class errorException : public std::exception {

private:
    std::string message;

public:
    errorException(std::string const& message_="Erreur inattendue") throw()
            : message(message_) {}

    virtual ~errorException() throw() {}

    virtual const char* what() const throw() {
        return message.c_str();
    }


};
