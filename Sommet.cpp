//
// Created by Antoine Hintzy on 16/03/2020.
//

#include "Sommet.h"

Sommet::Sommet(int num) : m_numero{num} {}


void Sommet::addSuccesseur(const Sommet* succ) {
    m_successeurs.push_back(succ);
}

const std::vector<const Sommet*>& Sommet::getSuccesseurs() const {
    return m_successeurs;
}

int Sommet::getNumero() const {
    return m_numero;
}

void Sommet::afficher() const {
    std::cout << "   Sommet " << m_numero << " : ";
    for(auto addrSommet : m_successeurs) {
        std::cout << addrSommet->getNumero() << " ";
    }
}

int Sommet::getSuccessDeg() const {
    return m_successeurs.size();
}
