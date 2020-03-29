#include <iostream>
#include "Graphe.h"

void afficherParcours(size_t s0, const std::vector<int>& precesseur) {
    for(size_t i = 0; i < precesseur.size(); ++i) {
        if (i != s0) {
            if(precesseur[i] != -1) {
                std::cout << i << " <--- ";
                size_t j = precesseur[i];
                while(j != s0) {
                    std::cout << j << " <--- ";
                    j = precesseur[j];
                }
                std::cout << j << std::endl;
            }
        }
    }
}

void afficherConnexite(std::vector<std::vector<int>> somConnex) {
    for(size_t i = 0; i < somConnex.size(); ++i) {
        std::cout << "Groupe connexe "<< i << " :" << std::endl;
        for (int j = 0; j < somConnex[i].size();++j){
            std::cout << somConnex[i][j] << std::endl;
        }
        std::cout << std::endl;
    }
}


int main() {
    size_t s0 = 0, s1=0;
    Graphe g{"../graphe-no-1.txt"};
    std::vector<int> arborescence;
    std::vector<std::vector<int>> somConnex;
    std::vector<std::vector<int>> somDeg;
    std::vector<int> cEurlerien;
    g.afficher();
    std::cout << std::endl << "BFS : Veuillez saisir le numéro du sommet initial pour la recherche du plus court chemin : ";
    std::cin >> s0;
    arborescence = g.BFS(s0);
    std::cout << "Plus courts chemins depuis le sommet " << s0 << " (BFS) : " << std::endl;
    afficherParcours(s0, arborescence);
    std::cout << std::endl << "DFS : Veuillez saisir le numéro du sommet initial pour la recherche du plus court chemin : ";
    std::cin >> s1;
    arborescence = g.DFS(s1);
    std::cout << "Plus courts chemins depuis le sommet " << s1 << " (DFS) : " << std::endl;
    afficherParcours(s1, arborescence);
    somConnex = g.connected();
    std::cout << std::endl << "----Connexité du graph-----" << std::endl;
    afficherConnexite(somConnex);
    somDeg = g.degGraph(somConnex);
    cEurlerien = g.graphEulerien(somDeg);
    std::cout << "----Circuit Eulérien-----" << std::endl;
    if (cEurlerien.size() == 0)
        std::cout << std::endl <<  "il n'y a pas de circuit Eulérien dans ce graph" << std::endl;
    else{
        std::cout <<  "Il y a un circuit Eulérien dans le(s) circuit(s) connexe(s) : " << std::endl;
        for (int i = 0; i < cEurlerien.size(); ++i) {
            std::cout << cEurlerien[i]<< " ";
        }
    }

    return 0;
}