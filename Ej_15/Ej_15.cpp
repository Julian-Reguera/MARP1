//Julián Reguera Peñalosa

#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

#define MAX 10000

using namespace std;

int operacion(int operacion, int numero) {
    switch (operacion) {
    case 0:
        return (numero + 1) % MAX;
        break;
    case 1:
        return (numero * 2) % MAX;
        break;
    case 2:
        return (numero / 3) % MAX;
        break;
    }
}

bool resuelveCaso() {

    int ini, fin;

    cin >> ini >> fin;

    if (!std::cin)
        return false;

    vector<bool> visitados(MAX, false);
    queue<int> Q;
    int numOp = 0, anchura = 1;

    visitados[ini] = true;
    Q.push(ini);

    while (!Q.empty() && Q.front() != fin) {
        int num = Q.front(); Q.pop();
        anchura--;

        for (int i = 0; i < 3; i++) {
            int aux = operacion(i, num);
            if (!visitados[aux]) {
                visitados[aux] = true;
                Q.push(aux);
            }
        }

        if (anchura == 0) {
            anchura = Q.size();
            numOp++;
        }
    }

    cout << numOp << "\n";

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