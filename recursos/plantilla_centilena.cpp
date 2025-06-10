// Julián Reguera Peñalosa

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


Solucion resolver(Datos datos) {
    ...
}


bool resuelveCaso() {

    // leer los datos de la entrada

    if (caso especial)
        return false;

    Solucion sol = resolver(datos);

    // escribir sol

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
