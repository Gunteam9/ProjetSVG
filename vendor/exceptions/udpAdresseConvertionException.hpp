//
// Created by gunteam on 13/02/2020.
//

#pragma once
#include <iostream>

class udpAdresseConvertionException : public std::exception {

private:
    std::string message;

public:
    udpAdresseConvertionException(std::string const& message_="Addresse IP non supporté") throw()
        : message(message_) {}

    virtual ~udpAdresseConvertionException() throw() {}

    virtual const char* what() const throw() {
        return message.c_str();
    }


};
