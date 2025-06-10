// Julián Reguera Peñalosa

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

bool resuelveCaso() {

    long long int esfuerzo = 0;
    int num;
    cin >> num;

    if (num == 0)
        return false;

    priority_queue<long long int, vector<long long int>, greater<long long int>> cola;

    for (int i = 0; i < num; i++) {
        long long int aux;
        cin >> aux;
        cola.push(aux);
    }

    while (cola.size() >= 2) {
        long long int res = cola.top();
        cola.pop();
        res += cola.top();
        cola.pop();
        esfuerzo += res;
        cola.push(res);
    }

    std::cout << esfuerzo << "\n";

    return true;
}


int main() {

    // ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("./casos.txt");
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
