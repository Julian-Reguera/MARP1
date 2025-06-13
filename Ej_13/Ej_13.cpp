//Julian Reguera Peñalosa

#include <iostream>
#include "Grafo.h"
#include "Problema.h"
#include <fstream>

using namespace std;

/*
Para resolver este problema lo que se hace es recorrer el vector por lo que el coste
es de orden n siendo n el número de vertices en el vector.
*/
bool resuelveCaso() {
    int usuarios, grupos;
    cin >> usuarios;
    cin >> grupos;

    if (!std::cin)
        return false;

    grupos--;

    Grafo grafo(usuarios);

    for (int i = 0; i <= grupos; i++) {
        int numIntegrantes, anterior = -1, actual = -1;
        cin >> numIntegrantes;
        if (numIntegrantes >= 1)
            cin >> anterior;
        anterior--;
        for (int e = 1; e < numIntegrantes; e++) {
            cin >> actual;
            actual--;
            grafo.ponArista(anterior, actual);
            anterior = actual;
        }
    }

    Problema problema(grafo);

    vector<int*> solucion = problema.buscarDifusion();

    for (int i = 0; i < solucion.size(); i++) {
        cout << *solucion[i] << " ";
    }

    cout << "\n";

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