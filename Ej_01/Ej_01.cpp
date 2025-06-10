//Julián Reguera Peñalosa


#include <iostream>
#include <fstream>
#include "bintree_eda.h"
using namespace std;

long minimo(long num1, long num2) {
    if (num1 > num2) return num2;
    else return num1;
}

long maximo(long num1, long num2) {
    if (num1 < num2) return num2;
    else return num1;
}

bool equilibrado(const bintree<long>& arbol, long& altura, long& min, long& max) {
    if (arbol.empty()) {
        return true;
    }
    else if (arbol.left().empty() && arbol.right().empty()) {
        altura = 1;
        min = arbol.root();
        max = arbol.root();
        return true;
    }
    else if (arbol.left().empty()) {
        long altDer, minDer, maxDer;
        bool eq = equilibrado(arbol.right(), altDer, minDer, maxDer);
        if (altDer > 1 || !eq || minDer <= arbol.root()) return false;
        else {
            altura = 2;
            min = arbol.root();
            max = maxDer;

            return true;
        }
    }
    else if (arbol.right().empty()) {
        long altHiz, minHiz, maxHiz;
        bool eq = equilibrado(arbol.left(), altHiz, minHiz, maxHiz);
        if (altHiz > 1 || !eq || maxHiz >= arbol.root()) return false;
        else {
            altura = 2;
            min = minHiz;
            max = arbol.root();

            return true;
        }
    }
    else {
        long altDer, minDer, maxDer, altHiz, minHiz, maxHiz;
        bool eqHiz = equilibrado(arbol.right(), altDer, minDer, maxDer);
        bool eqDer = equilibrado(arbol.left(), altHiz, minHiz, maxHiz);

        if (!eqHiz || !eqDer || minDer <= arbol.root() || maxHiz >= arbol.root() || abs(altHiz - altDer) > 1) return false;
        else
        {
            min = minHiz;
            max = maxDer;
            altura = maximo(altDer, altHiz) + 1;
            return true;
        }
    }
}

void resuelveCaso() {
    bintree<long> arbol = leerArbol((long)-1);
    long min, max, alt;
    bool res = equilibrado(arbol, alt, min, max);

    if (res) cout << "SI" << endl;
    else cout << "NO" << endl;
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