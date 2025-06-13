//Julián Reguera Peñalosa

#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

#include "Grafo.h"

using namespace std;

bool dfs(const Grafo& graf, int vertice, vector<bool>& visitado, int origen) {
    if (visitado[vertice]) return false;

    visitado[vertice] = true;

    for (int v : graf.ady(vertice)) {
        if (origen != v) {
            if (!dfs(graf, v, visitado, vertice)) return false;
        }
    }

    return true;
}

bool resuelveCaso() {

    int vertices, aristas;

    cin >> vertices >> aristas;

    if (!std::cin)
        return false;

    Grafo graf(vertices);
    vector<bool> visitados(vertices, false);

    for (int i = 0; i < aristas; i++) {
        int inici, fin;

        cin >> inici >> fin;

        graf.ponArista(inici,fin);
    }

    bool resultado = dfs(graf, 0, visitados,-1);
    int i = 0;

    while (resultado && i< vertices) {
        resultado = resultado && visitados[i];
        i++;
    }

    if (resultado)
        cout << "SI\n";
    else
        cout << "NO\n";

    return true;
}


int main() {

    // ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // restablecimiento de cin
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("pause");
#endif
    return 0;
}