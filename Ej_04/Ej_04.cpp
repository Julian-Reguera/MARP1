// Julián Reguera Peñalosa

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

struct notificacion {
    long long int siguiente;
    long long int intervalo;
    long long int identificador;

    bool operator < (const notificacion& not1) const{
        return not1.siguiente == siguiente ? identificador > not1.identificador : siguiente > not1.siguiente;
    }
};

bool resuelveCaso() {

    int numUsuarios,numEnvios;
    cin >> numUsuarios;

    if (numUsuarios == 0)
        return false;

    priority_queue<notificacion> Q;

    for (int i = 0; i < numUsuarios; i++) {
        long long int id, intervalo;

        cin >> id >> intervalo;
        Q.push({intervalo, intervalo, id});
    }

    cin >> numEnvios;

    for (int i = 0; i < numEnvios; i++) {
        notificacion aux = Q.top(); Q.pop();

        cout << aux.identificador << "\n";

        aux.siguiente += aux.intervalo;
        Q.push(aux);
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
