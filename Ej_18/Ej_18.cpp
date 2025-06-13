// Julián Reguera Peñalosa

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

int siguiente(int pos, int tirada, const unordered_map<int, int>& especiales) {
    int aux = pos + tirada;

    if (especiales.count(aux)) {
        return especiales.at(aux);
    }
    else{
        return aux;
    }
}

bool resuelveCaso() {

    int dimensiones, carasDado, numSerpientes, numEscaleras;
    unordered_map<int,int> especiales;

    cin >> dimensiones >> carasDado >> numSerpientes >> numEscaleras;

    if (dimensiones == 0 && carasDado == 0 && numSerpientes == 0 && numEscaleras == 0)
        return false;

    for (int i = 0; i < numSerpientes + numEscaleras; i++) {
        int ini, fin;
        cin >> ini >> fin;
        especiales[ini-1] = fin-1;
    }

    vector<bool> visitados(dimensiones * dimensiones, false);
    queue<int> Q;
    int nivel = 0, anchura = 1;
    int meta = dimensiones * dimensiones - 1;

    visitados[0] = true;
    Q.push(0);

    while (!Q.empty() && Q.front() != meta) {
        int casilla = Q.front(); Q.pop();
        anchura--;

        for (int i = 1; i <= carasDado;i++) {
            int aux = siguiente(casilla, i, especiales);

            if (aux <= meta && !visitados[aux]) {
                visitados[aux] = true;
                Q.push(aux);
            }
        }

        if (anchura == 0) {
            anchura = Q.size();
            nivel++;
        }
    }

    cout << nivel << "\n";

    return true;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
