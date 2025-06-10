// Julián Reguera Peñalosa

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

struct paciente {
    string nombre;
    int gravedad;
    int id;

    bool operator < (const paciente& p1) const {
        return gravedad == p1.gravedad ? id > p1.id : gravedad < p1.gravedad;
    }
};

bool resuelveCaso() {

    int numEventos,id =0;

    cin >> numEventos;

    if (numEventos == 0)
        return false;

    priority_queue<paciente> Q;

    for (int i = 0; i < numEventos; i++) {
        char letra;

        cin >> letra;

        if (letra == 'I') {
            paciente p;

            cin >> p.nombre >> p.gravedad;
            p.id = id;
            id++;

            Q.push(p);
        }
        else {
            paciente p = Q.top(); Q.pop();

            cout << p.nombre << "\n";
        }
    }

    cout << "---\n";

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
