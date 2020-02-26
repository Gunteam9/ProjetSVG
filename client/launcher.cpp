//
// Created by Romain on 11/02/2020.
//

#include "include/functions.hpp"

using namespace std;

int main() {

    functions func;

    //cbor::binary data = func.entry();

    cbor::map data = {
            { "sun_x", "5.0"},
            { "sun_y", "2.0" }
    };

    for (auto it = data.begin(); it != data.end(); ++it) {
        cout << (string) it->first << " " << (string) it->second << endl;
    }

    func.sendData(data);

    return 0;
}