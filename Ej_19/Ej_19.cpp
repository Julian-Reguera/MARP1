//Julián Reguera Peñalosa

#include <iostream>
#include <vector>
#include <fstream>

#include "ConjuntosDisjuntos.h"

using namespace std;

const int direcciones[8][2] = { {1,-1},{1,0},{1,1},{0,-1},{0,1},{-1,-1},{-1,0},{-1,1} };

void conexiones(int ancho, int alto, const vector<vector<char>>& tablero, ConjuntosDisjuntos& cd,int x, int y) {
    int actual = y * ancho + x;

    for (int i = 0; i < 8; i++) {
        int xAux = x + direcciones[i][0];
        int yAux = y + direcciones[i][1];

        if (xAux >= 0 && xAux < ancho && yAux>=0 && yAux < alto && tablero[yAux][xAux] == '#') {
            int nuevo = yAux * ancho + xAux;
            cd.unir(actual, nuevo);
        }
    }
}

bool resuelveCaso() {

    int alto, ancho, numEventos;

    cin >> alto >> ancho;

    if (!std::cin)
        return false;


    vector<vector<char>> tablero(alto,vector<char>(ancho));
    ConjuntosDisjuntos cd(alto*ancho);
    int maximo = 0;

    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho; j++) {
            cin >> tablero[i][j];
            if (tablero[i][j] == '#') {
                conexiones(ancho, alto, tablero, cd, j, i);
                maximo = max(maximo, cd.tam(ancho*i+j));
            }
        }
    }
    cout << maximo << " ";
    cin >> numEventos;

    for (int i = 0; i < numEventos; i++) {
        int y, x;
        cin >> y >> x;

        y--;
        x--;

        tablero[y][x] = '#';
        conexiones(ancho, alto, tablero, cd, x, y);
        maximo = max(maximo, cd.tam(ancho * y + x));

        cout << maximo << " ";
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