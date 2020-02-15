#include "message.hpp"

#include <tinyxml2.h>

class Event {
    private:
        tinyxml2::XMLElement* element;
        Message* message;
    public:
        Event(tinyxml2::XMLElement*, Message*);
        ~Event();
        tinyxml2::XMLElement* getElement();
        Message* getMessage();
};