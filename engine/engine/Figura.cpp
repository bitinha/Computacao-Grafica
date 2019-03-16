#include "Figura.h"
#include <vector>
#include "Transformacao.h"
#define strdup _strdup

Figura::Figura(vector<Transformacao> trans, char * f)
{
	this->transformacoes = trans;
	this->file = strdup(f);

}

Figura::~Figura()
{
}

vector<Transformacao> Figura::getTransformacoes() {
	return this->transformacoes;
}

void Figura::setTransformacoes(vector<Transformacao> trans) {
	this->transformacoes = trans;
}

char* Figura::getFile() {
	return this->file;
}

void Figura::setFile(char* f) {
	this->file = strdup(f);
}