#include <vector>
#include "Transformacao.h"
#pragma once
using namespace std;
class Grupo
{
public: vector<Transformacao> transformacoes;
		vector<float> pontos;
		vector<Grupo> grupos;
		Grupo(vector<Transformacao> trans, vector<float> p, vector<Grupo> grupos);
		Grupo();
		~Grupo();
		vector<Transformacao> getTranformacoes();
		vector<float> getPontos();
		void setTransformacoes(vector<Transformacao> trans);
		void setPontos(vector<float> p);
		void addPontos(vector<float> pontos);
		void addGrupo(Grupo g);
		int tamanhoGrupo();
		void draw();
};