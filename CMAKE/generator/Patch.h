#pragma once

#include "Ponto.h"
#include <vector>
using namespace std;
class Patch
{
public: vector<int> indices;
		vector<Ponto*> pontos; //Pontos na ordem necessária para desenhar os triangulos do patch

		Patch();
		~Patch();
		vector<int> getIndices();
		vector<Ponto*> getPontos();
		void setIndices(vector<int> indices);
		void addIndice(int indice);
		void geraPontos(vector<Ponto*> cp, int tesselation);
};