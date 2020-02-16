
#include "include/erreurException.hpp"

ErreurException::ErreurException(const string &phrase) throw() {
    this->m_phrase=phrase;
}

const char *ErreurException::what() const throw() {
    return m_phrase.c_str();
}
