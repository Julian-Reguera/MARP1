#pragma once
#include <stdlib.h>
#include <vector>
#include "Grafo.h"
#include <stack>

using namespace std;

class Problema {
public:
	Problema() {
	}

	Problema(Grafo grafo) {
		vectorSol.resize(grafo.V());
		vector<bool> visitados(grafo.V(), false);
		vector<bool> visitados2(grafo.V(), false);

		for (int i = 0; i < grafo.V(); i++) {
			if (!visitados[i]) {
				int* aux = new int;
				*aux = 0;
				_tamanoGrupo(grafo, visitados, aux, i);

			}
		}
	}

	const vector<int*> buscarDifusion() {
		return vectorSol;
	}
private:
	vector<int*> vectorSol;
	void _tamanoGrupo(const Grafo& grafo, vector<bool>& visitados, int* predecesor, int vertice) {
		vectorSol[vertice] = predecesor;
		*vectorSol[vertice] = *vectorSol[vertice] + 1;
		visitados[vertice] = true;
		vector<int> vecinos = grafo.ady(vertice);


		for (int i = 0; i < vecinos.size(); i++) {
			if (!visitados[vecinos[i]])
				_tamanoGrupo(grafo, visitados, predecesor, vecinos[i]);
		}
	}
};