//
// Created by gunteam on 11/02/2020.
//

#pragma once

#include <iostream>

class udpRuntimeException : public std::exception {

public:
    udpRuntimeException(const std::string addr, const int port);
};

