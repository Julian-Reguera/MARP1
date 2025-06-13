// Julián Reguera Peñalosa

#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;


bool resuelveCaso() {

    int N, A, B, i;

    cin >> N >> A >> B;

    if (!std::cin)
        return false;

    priority_queue<int, vector<int>, less<int>> colaPilasA;
    priority_queue<int, vector<int>, less<int>> colaPilasB;

    for (int e = 0; e < A; e++) {
        int tiempo;
        cin >> tiempo;
        colaPilasA.push(tiempo);
    }

    for (int e = 0; e < B; e++) {
        int tiempo;
        cin >> tiempo;
        colaPilasB.push(tiempo);
    }

    while (!colaPilasA.empty() && !colaPilasB.empty()) { //bucle de semanas
        int tiempo = 0;
        i = 0;
        vector<int> pilaAReutilizables;
        vector<int> pilaBReutilizables;

        while (i < N && !colaPilasA.empty() && !colaPilasB.empty()) {
            int tiempoA = colaPilasA.top();
            int tiempoB = colaPilasB.top();
            tiempo += min(tiempoA, tiempoB);

            if (tiempoA > tiempoB) {
                pilaAReutilizables.push_back(tiempoA - tiempoB);
            }
            else if (tiempoB > tiempoA) {
                pilaBReutilizables.push_back(tiempoB - tiempoA);
            }

            colaPilasA.pop();
            colaPilasB.pop();

            i++;
        }

        for (int e = 0; e < pilaAReutilizables.size(); e++) {
            colaPilasA.push(pilaAReutilizables[e]);
        }

        for (int e = 0; e < pilaBReutilizables.size(); e++) {
            colaPilasB.push(pilaBReutilizables[e]);
        }

        cout << tiempo << " ";
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