// Julián Reugera Peñalosa

#include <iostream>
#include <fstream>
#include <queue>
#include "Grafo.h"

using namespace std;

int mensaje(const Grafo& grafo, int nodo, int TTL) {
    vector<bool> marcado(grafo.V(), false);
    queue<int> aux;
    int saltos = 0, anchura = 1, visitados = 0;

    marcado[nodo] = true;
    aux.push(nodo);

    while (!aux.empty() && saltos <= TTL) {
        int elem = aux.front();
        aux.pop();
        vector<int> adyacentes = grafo.ady(elem);
        visitados++;

        for (int i = 0; i < adyacentes.size(); i++) {
            if (!marcado[adyacentes[i]]) {
                marcado[adyacentes[i]] = true;
                aux.push(adyacentes[i]);
            }
        }

        anchura--;

        if (anchura == 0) {
            anchura = aux.size();
            saltos++;
        }
    }

    return visitados;
}

bool resuelveCaso() {

    int vertices, aristas;
    cin >> vertices;
    cin >> aristas;

    if (!std::cin)
        return false;

    Grafo grafo(vertices);

    for (int i = 0; i < aristas; i++) {
        int origen, destino;
        cin >> origen;
        cin >> destino;
        grafo.ponArista(origen - 1, destino - 1);
    }

    int consultas;

    cin >> consultas;

    for (int i = 0; i < consultas; i++) {
        int origen, ttl;
        cin >> origen;
        cin >> ttl;
        int res = mensaje(grafo, origen - 1, ttl);
        cout << vertices - res << "\n";
    }

    cout << "---\n";

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