//
// Created by Romain on 11/02/2020.
//

#include "include/functions.hpp"

using namespace std;

int main() {

    functions func;

    //cbor::binary data = func.entry();

    cbor::map message = {
            { "sun_x", 5.0 },
            { "sun_y", 2.0 }
    };

    cbor::binary data = cbor::encode(message);

    func.sendData(data);

    return 0;
}