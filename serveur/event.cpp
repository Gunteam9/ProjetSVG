#include "event.hpp"

Event::Event(tinyxml2::XMLElement* element, Message* m){
    this->element = element;
    this->message = m;
}

Event::~Event(){

}

tinyxml2::XMLElement* Event::getElement(){
    return this->element;
}

Message* Event::getMessage(){
    return this->message;
}

