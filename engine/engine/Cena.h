#include <vector>
#include "Transformacao.h"
#pragma once
using namespace std;
class Cena
{
public: vector<Transformacao> transformacoes;
		vector<float> pontos;
	Cena(vector<Transformacao> trans, vector<float> p);
	~Cena();
	virtual vector<Transformacao> getTranformacoes();
	virtual vector<float> getPontos();
	virtual void setTransformacoes(vector<Transformacao> trans);
	virtual void setPontos(vector<float> p);
	void aplicaTransformacoes();
};