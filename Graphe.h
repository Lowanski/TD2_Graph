//
// Created by Antoine Hintzy on 16/03/2020.
//

#ifndef TP2_TG_GRAPHE_H
#define TP2_TG_GRAPHE_H

#include <iostream>
#include <vector>
#include <string>
#include "Sommet.h"

class Graphe {
private:
    bool m_estOriente;
    std::vector<Sommet*> m_sommets;
public:
    Graphe(std::string cheminFichierGraphe);
    ~Graphe();
    void afficher() const;
    std::vector<int> BFS(int numero_s0) const;
    std::vector<int> DFS(int numero_s0) const;
    std::vector<std::vector<int>> connected() const;
    std::vector<std::vector<int>> degGraph(std::vector<std::vector<int>> components) const;
    std::vector<int> graphEulerien(std::vector<std::vector<int>> somDeg);
};


#endif //TP2_TG_GRAPHE_H
