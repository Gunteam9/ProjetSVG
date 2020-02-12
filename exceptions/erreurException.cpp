
#include "erreurException.hpp"

Erreur::Erreur(const string &phrase) throw() {
    this->m_phrase=phrase;
}

const char *Erreur::what() const throw() {
    return m_phrase.c_str();
}
