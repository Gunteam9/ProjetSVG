//
// Created by gunteam on 11/02/2020.
//

#pragma once
#include <stdexcept>

class udpSendingException : public std::exception {



public:
    udpSendingException();

    udpSendingException(const char* message);
};
