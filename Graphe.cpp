#include "Sommet.h"
#include "Graphe.h"
#include <fstream>
#include <queue>
#include <unordered_map>

Graphe::Graphe(std::string cheminFichierGraphe) {
    std::ifstream ifs{cheminFichierGraphe};
    if (!ifs) {
        throw std::runtime_error("Impossible d'ouvrir " + cheminFichierGraphe);
    }
    ifs >> m_estOriente;
    if (ifs.fail()) {
        throw std::runtime_error("Problème de lecture de l'orientation du graphe.");
    }
    int ordre;
    ifs >> ordre;
    if (ifs.fail()) {
        throw std::runtime_error("Problème de lecture de l'ordre du graphe.");
    }
    int taille;
    ifs >> taille;
    if (ifs.fail()) {
        throw std::runtime_error("Problème de lecture de la taille du graphe.");
    }
    for (int i = 0; i < ordre; ++i) {
        m_sommets.push_back(new Sommet(i));
    }
    int num1, num2;
    for (int i = 0; i < taille; ++i) {
        ifs >> num1 >> num2;
        if (ifs.fail()) {
            throw std::runtime_error("Problème de lecture d'un.e arc/arête.");
        }
        m_sommets[num1]->addSuccesseur(m_sommets[num2]);
        if (!m_estOriente && num1 < num2) {
            m_sommets[num2]->addSuccesseur(m_sommets[num1]);
        }
    }
}

Graphe::~Graphe() {
    for (auto addrSommet : m_sommets) {
        delete addrSommet;
    }
}

void Graphe::afficher() const {
    std::cout << std::endl << "Graphe ";
    std::cout << (m_estOriente ? "orienté" : "non orienté") << std::endl;
    std::cout << "Ordre : " << m_sommets.size() << std::endl;
    std::cout << "Liste d'adjacences : " << std::endl;
    for (auto addrSommet : m_sommets) {
        addrSommet->afficher();
        std::cout << std::endl;
    }

}

// Algo parcoursBFS(s0)
std::vector<int> Graphe::BFS(int numero_s0) const {
    // 1. Tous les sommets sont blancs (non découverts)
    std::vector<int> couleurs((int) m_sommets.size(), 0);
    // 2. Créer une file vide
    std::queue<const Sommet *> file;
    std::vector<int> predecesseurs((int) m_sommets.size(), -1);
    // 3. Enfiler s0 ; s0 devient gris
    file.push(m_sommets[numero_s0]);
    couleurs[numero_s0] = 1; // 0 = blanc, 1 = gris, 2 = noir
    const Sommet *s;
    // 4. Tant que la file n’est pas vide :
    while (!file.empty()) {
        // 4.1 Défiler le prochain sommet s de la file (Traitement éventuel sur s)
        s = file.front();
        file.pop();
        // 4.2 Pour chaque successeur s’ blanc (non découvert) de s :
        for (auto succ : s->getSuccesseurs()) {
            if (couleurs[succ->getNumero()] == 0) { // blanc
                // 4.2.1 Enfiler s’; s’ devient gris
                file.push(succ);
                couleurs[succ->getNumero()] = 1; // gris
                // 4.2.2 Noter que s est le prédécesseur de s’
                predecesseurs[succ->getNumero()] = s->getNumero();
            }
        }
        // 4.3 s devient noir (exploré)
        couleurs[s->getNumero()] = 2;
    }
    return predecesseurs;
}

std::vector<int> Graphe::DFS(int numero_s0) const {
    // 1. Tous les sommets sont blancs (non découverts)
    std::vector<int> couleurs((int) m_sommets.size(), 0);
    // 2. Créer une file vide
    std::stack<const Sommet *> file;
    std::vector<int> predecesseurs((int) m_sommets.size(), -1);
    // 3. Enfiler s0 ; s0 devient gris
    file.push(m_sommets[numero_s0]);
    couleurs[numero_s0] = 1; // 0 = blanc, 1 = gris, 2 = noir
    const Sommet *s;
    // 4. Tant que la file n’est pas vide :
    while (!file.empty()) {
        // 4.1 Défiler le prochain sommet s de la file (Traitement éventuel sur s)
        s = file.top();
        file.pop();
        // 4.2 Pour chaque successeur s’ blanc (non découvert) de s :
        for (auto succ : s->getSuccesseurs()) {
            if (couleurs[succ->getNumero()] == 0) { // blanc et gris
                // 4.2.1 Enfiler s’; s’ devient gris
                file.push(succ);
                couleurs[succ->getNumero()] = 1; // gris
                // 4.2.2 Noter que s est le prédécesseur de s’
                predecesseurs[succ->getNumero()] = s->getNumero();
            }
        }
        // 4.3 s devient noir (exploré)
        couleurs[s->getNumero()] = 2;
    }
    return predecesseurs;
}

std::vector<std::vector<int>> Graphe::connected() const {
    std::vector<int> couleurs((int) m_sommets.size(), 0);
    std::vector<std::vector<int>> components;
    for (int i = 0; i < m_sommets.size(); ++i) {
        std::vector<int> component;
        if (couleurs[i] != 2) {
            component.push_back(i);
            couleurs[i] = 1;
            std::vector<int> dfspred = DFS(i);
            int j = -1;
            for (auto vertex :dfspred) {
                j++;
                if (vertex >= 0)
                    if (couleurs[j] == 0) {
                        component.push_back(j);
                        couleurs[j] = 2;
                    }

            }
            if (component.size()) {
                components.push_back(component);
            }
        }

    }
    return components;
}

std::vector<std::vector<int>> Graphe::degGraph(std::vector<std::vector<int>> components) const {
    std::vector<std::vector<int>> degEulerien;
    for (int i = 0; i < components.size(); ++i) {
        std::vector<int> degSommet;
        for(auto j : components[i]){
            int degSom = 0;
            degSom = m_sommets[j]->getSuccessDeg();
            degSommet.push_back(degSom);
        }
        degEulerien.push_back(degSommet);
    }
    return degEulerien;
}

std::vector<int> Graphe::graphEulerien(std::vector<std::vector<int>> somDeg) {
    std::vector<int> circuitEul;
    for (int i = 0; i < somDeg.size(); ++i) {
        int degImp = -1;
        int somDegImp = 0;
        for(auto it : somDeg[i]){
            degImp = it%2;
            somDegImp = somDegImp + degImp;
        }
            if (somDegImp == 0 || somDegImp == 2)
                circuitEul.push_back(i);
    }
    return  circuitEul;
}


