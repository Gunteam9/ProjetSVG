//
// Created by gunteam on 13/02/2020.
//

#pragma once
#include <iostream>

class udpBindsException : public std::exception {

private:
    std::string message;

public:
    udpBindsException(std::string const& message_="Binding impossible") throw()
            : message(message_) {}

    virtual ~udpBindsException() throw() {}

    virtual const char* what() const throw() {
        return message.c_str();
    }


};
