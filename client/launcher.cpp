//
// Created by Romain on 11/02/2020.
//

#include "functions.h"
#include "../cbor11/cbor11.hpp"

using namespace std;

int main() {

    functions func;

    cbor test = "toto";

    func.sendData(test);

    return 0;
}