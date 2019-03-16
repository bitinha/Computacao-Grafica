#include "Cena.h"

using namespace std;

Cena::Cena(vector<Transformacao> trans, vector<float> p){
	this->transformacoes = trans;
	this->pontos = p;
}

Cena::~Cena()
{
}

vector<Transformacao> Cena::getTranformacoes() {
	return this->transformacoes;
}

vector<float> Cena::getPontos() {
	return this->pontos;
}

void Cena:: setTransformacoes(vector<Transformacao> trans) {
	this->transformacoes = trans;
}

void Cena::setPontos(vector<float> p) {
	this->pontos = p;
}
