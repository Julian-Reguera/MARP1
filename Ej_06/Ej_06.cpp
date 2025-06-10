// Julián Reguera Peñalosa

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

struct caja {
    int id;
    int siguiente;

    bool operator <(const caja& c1) const {
        return siguiente == c1.siguiente ? id > c1.id : siguiente > c1.siguiente;
    }
};

bool resuelveCaso() {

    int numCajas, numClientes;

    cin >> numCajas >> numClientes;

    if (numCajas == 0 && numClientes == 0)
        return false;

    priority_queue<caja> Q;

    for (int i = 1; i <= numCajas; i++) {
        Q.push({ i,0 });
    }
    
    for (int i = 0; i < numClientes; i++) {
        caja aux = Q.top(); Q.pop();
        int tiempo;

        cin >> tiempo;

        aux.siguiente += tiempo;
        Q.push(aux);
    }

    cout << Q.top().id << "\n";

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
