//Julián Reguera Peñalosa

#include <iostream>
#include <fstream>
#include <vector>

#include "Grafo.h"

using namespace std;


int tamGrupo(const Grafo& graf, int vertice, vector<bool>& visitados) {
    if (visitados[vertice]) return 0;

    visitados[vertice] = true;

    int res = 1;
    for (int v: graf.ady(vertice)) {
        res += tamGrupo(graf,v,visitados);
    }

    return res;
}

void resuelveCaso() {
    int vertices, aristas;
    
    cin >> vertices >> aristas;

    vector<bool> visitados(vertices,false);
    Grafo graf(vertices);

    for (int i = 0; i < aristas; i++) {
        int ini, fin;
        cin >> ini >> fin;

        graf.ponArista(ini-1,fin-1);
    }

    int maximo = 0;

    for (int i = 0; i < vertices; i++) {
        maximo = max(maximo, tamGrupo(graf,i,visitados));
    }

    cout << maximo << "\n";
}

int main() {
    // Para la entrada por fichero.
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif


    unsigned int numCasos;
    std::cin >> numCasos;
    // Resolvemos
    for (int i = 0; i < numCasos; ++i) {
        resuelveCaso();
    }


#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}