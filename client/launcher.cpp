//
// Created by Romain on 11/02/2020.
//

#include "include/view.hpp"
#include "include/functions.hpp"

using namespace std;

int main(int argc, char *argv[]) {

    view v = view::getInstance();

    v.setWidth(500);
    v.setHeight(500);
    v.setTitre("Moteur de rendu SVG");

    v.init(&argc, &argv);


    std::thread t(view::start, &v);

/*
    functions func;

    cbor::map data = {
            { "?", "?"},
    };


    func.sendData(data);

 */
    return 0;
}