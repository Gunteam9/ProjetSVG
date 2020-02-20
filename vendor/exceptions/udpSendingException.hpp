//
// Created by gunteam on 13/02/2020.
//

#pragma once
#include <iostream>

class udpSendingException : public std::exception {

private:
    std::string message;

public:
    udpSendingException(std::string const& message_="Impossible d'envoyer le message") throw()
            : message(message_) {}

    virtual ~udpSendingException() throw() {}

    virtual const char* what() const throw() {
        return message.c_str();
    }


};
