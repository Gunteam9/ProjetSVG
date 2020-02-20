//
// Created by gunteam on 13/02/2020.
//

#pragma once
#include <iostream>

class udpReceiveException : public std::exception {

private:
    std::string message;

public:
    udpReceiveException(std::string const& message_="Impossible de recevoir le message") throw()
            : message(message_) {}

    virtual ~udpReceiveException() throw() {}

    virtual const char* what() const throw() {
        return message.c_str();
    }


};
