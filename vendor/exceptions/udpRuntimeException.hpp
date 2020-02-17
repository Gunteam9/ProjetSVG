//
// Created by gunteam on 13/02/2020.
//

#pragma once
#include <iostream>

class udpRuntimeException : public std::exception {

private:
    std::string message = "Impossible de créer la socket pour ";
    std::string ip;
    int port;

    std::string result;

public:
    udpRuntimeException(std::string const& ip_="127.0.0.2", int const& port_=6789) throw()
            : ip(ip_), port(port_) {
        result = message + "(" + ip + ":" + std::to_string(port) + ")";
    }

    udpRuntimeException(std::string const& message_="Impossible de créer la socket pour ", std::string const& ip_="127.0.0.2", int const& port_=6789) throw()
            : message(message_), ip(ip_), port(port_) {
        result = message + "(" + ip + ":" + std::to_string(port) + ")";
    }

    virtual ~udpRuntimeException() throw() {}

    virtual const char* what() const throw() {
        return result.c_str();
    }


};
