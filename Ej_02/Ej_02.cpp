//Julian Reguera Penalosa

#include <iostream>
#include "TreeSet_AVL.h"
#include <fstream>

using namespace std;

bool resuelveCaso() {

    int N, M;
    Set<int> arbol;

    cin >> N;
    if (N == 0)
        return false;

    for (int i = 0; i < N; i++) {
        int aux;
        cin >> aux;
        arbol.insert(aux);
    }

    cin >> M;

    for (int i = 0; i < M; i++) {
        int aux;
        cin >> aux;
        try {
            cout << arbol.kesimo(aux) << endl;
        }
        catch (const std::runtime_error& e) {
            cout << "??" << endl;
        }
    }

    cout << "---" << endl;

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