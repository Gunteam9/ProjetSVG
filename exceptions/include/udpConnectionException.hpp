//
// Created by gunteam on 13/02/2020.
//

#pragma once
#include <iostream>

class udpConnectionException : public std::exception {

public:
    udpConnectionException(const std::string addr, const int port);

};
