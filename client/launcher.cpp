//
// Created by Romain on 11/02/2020.
//

#include "include/functions.hpp"

using namespace std;

int main() {

    functions func;

    //cbor::binary data = func.entry();

    cbor::map data = {
            { "?", "?"},
    };


    /*for (auto it = data.begin(); it != data.end(); ++it) {
        cout << (string) it->first << " " << (string) it->second << endl;
    }
*/
    func.sendData(data);

    return 0;
}