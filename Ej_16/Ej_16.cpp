//Julián Reguera Peñalosa

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

const int direcciones[4][2] = {{-1,0},{1,0},{0,1},{0,-1}};

struct pos {
    int x;
    int y;
};

vector<pos> adyacente(int ancho, int alto, pos actual) {
    vector<pos> res;

    for (int i = 0; i < 4; i++) {
        pos aux;
        aux.x = actual.x + direcciones[i][0];
        aux.y = actual.y + direcciones[i][1];

        if (aux.x >= 0 && aux.x < ancho && aux.y >= 0 && aux.y < alto) {
            res.push_back(aux);
        }
    }

    return res;
}

int tamanoMancha(const vector<vector<char>>& tablero, vector<vector<bool>>& marcados,const pos& ini) {
    int y = ini.y, x = ini.x;

    if (marcados[y][x])
        return 0;

    marcados[y][x] = true;

    if (tablero[y][x] != '#')
        return 0;

    int res = 1;
    vector<pos> ady = adyacente(tablero[0].size(), tablero.size(), ini);

    for (pos p: ady) {
        res += tamanoMancha(tablero, marcados, p);
    }

    return res;
}

bool resuelveCaso() {

    int alto, ancho;

    cin >> alto >> ancho;

    if (!std::cin)
        return false;

    vector<vector<char>> tablero(alto, vector<char>(ancho));
    vector<vector<bool>> marcados(alto, vector<bool>(ancho, false));
    int numManchas = 0, maxMancha = 0;;

    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho; j++) {
            cin >> tablero[i][j];
        }
    }

    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho; j++) {
            if (!marcados[i][j] && tablero[i][j] == '#') {
                numManchas++;
                maxMancha = max(maxMancha, tamanoMancha(tablero, marcados, {j,i}));
            }
        }
    }

    cout << numManchas << " " << maxMancha << "\n";

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