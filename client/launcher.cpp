//
// Created by Romain on 11/02/2020.
//

#include "include/functions.hpp"

using namespace std;

int main() {

    functions func;

    //cbor::binary data = func.entry();

    cbor::map data = {
            { "sun_x", "50.0"},
            { "sun_y", "50.0" }
    };

    func.sendData(data);

    return 0;
}