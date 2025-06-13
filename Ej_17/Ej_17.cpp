//Julián Reguera Peñalosa

#include <iostream>
#include <vector>
#include <fstream>
#include <stack>

#include "Digrafo.h"

using namespace std;

bool ordenTareas(const Digrafo& graf, int ini, stack<int>& res, vector<bool>& visitados, vector<bool>& pila) {
    //si esta en la pila hay un ciclo y no se pueden realizar las tareas
    if (pila[ini])
        return false;

    //si no esta en la pila pero si se ha visitado significa que ya se ha añadido al stack
    if (visitados[ini])
        return true;

    visitados[ini] = true;
    pila[ini] = true;

    bool acabable = true;
    for (int num : graf.ady(ini)) {
        acabable = acabable && ordenTareas(graf, num, res,visitados,pila);
    }

    pila[ini] = false;
    res.push(ini);

    return acabable;
}

bool resuelveCaso() {

    int numTareas, numAristas;

    cin >> numTareas >> numAristas;

    if (!std::cin)
        return false;

    Digrafo graf(numTareas);
    vector<bool> visitados(numTareas, false);
    vector<bool> pila(numTareas, false);

    for (int i = 0; i < numAristas;  i++) {
        int ini, fin;
        cin >> ini >> fin;

        graf.ponArista(ini-1,fin-1);
    }

    bool acabable = true;
    stack<int> res;

    for (int i = 0; i < numTareas; i++) {
        if (!visitados[i] && acabable) {
            acabable = acabable && ordenTareas(graf,i,res,visitados,pila);
        }
    }

    if (acabable) {
        while (!res.empty()) {
            cout << res.top()+1 << " ";
            res.pop();
        }
    }
    else {
        cout << "Imposible";
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