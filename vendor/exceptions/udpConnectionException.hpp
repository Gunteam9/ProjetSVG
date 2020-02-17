//
// Created by gunteam on 13/02/2020.
//

#pragma once
#include <iostream>

class udpConnectionException : public std::exception {

private:
    std::string message = "Connexion au serveur impossible ";
    std::string ip;
    int port;

    std::string result;

public:
    udpConnectionException(std::string const& ip_="127.0.0.2", int const& port_=6789) throw()
            : ip(ip_), port(port_) {
        result = message + "(" + ip + ":" + std::to_string(port) + ")";
    }

    udpConnectionException(std::string const& message_="Connexion au serveur impossible ", std::string const& ip_="127.0.0.2", int const& port_=6789) throw()
            : message(message_), ip(ip_), port(port_) {
        result = message + "(" + ip + ":" + std::to_string(port) + ")";
    }

    virtual ~udpConnectionException() throw() {}

    virtual const char* what() const throw() {
        return result.c_str();
    }


};
