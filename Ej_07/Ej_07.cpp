// Julián Reguera Peñalosa

#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

struct tarea_t {
    int id;
    long long int inicio;
    long long int fin;
    bool repetitiva;
    long long int periodo;
};

bool operator>(tarea_t const& a, tarea_t const& b) {
    return a.inicio == b.inicio ? a.id > b.id : a.inicio > b.inicio;
}

bool resuelveCaso() {

    int N, M, T;
    long long int tiempo = 0;

    cin >> N >> M >> T;
    if (!std::cin)
        return false;

    priority_queue<tarea_t, vector<tarea_t>, greater<tarea_t>> cola;

    for (int i = 0; i < N; i++) {
        tarea_t tarea;
        tarea.id = i;
        cin >> tarea.inicio >> tarea.fin;
        tarea.repetitiva = false;
        cola.push(tarea);
    }

    for (int i = 0; i < M; i++) {
        tarea_t tarea;
        tarea.id = i + N;
        cin >> tarea.inicio >> tarea.fin >> tarea.periodo;
        tarea.repetitiva = true;
        cola.push(tarea);
    }

    while (!cola.empty() && cola.top().inicio >= tiempo && tiempo <= T) {
        tarea_t tarea = cola.top();
        cola.pop();

        tiempo = tarea.fin;

        if (tarea.repetitiva) {
            tarea.inicio += tarea.periodo;
            tarea.fin += tarea.periodo;
            cola.push(tarea);
        }
    }

    if (!cola.empty() && cola.top().inicio < tiempo && cola.top().inicio < T) {
        cout << "SI\n";
    }
    else {
        cout << "NO\n";
    }
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
