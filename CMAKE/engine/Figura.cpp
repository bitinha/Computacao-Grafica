#include "Figura.h"


Figura::Figura()
{
}


Figura::~Figura()
{
}

vector<float> Figura::getPontos() {
	return this->pontos;
}

void Figura::setPontos(vector<float> pontos) {
	this->pontos = pontos;
}

void Figura::setBuffer(GLuint buf) {
	this->buffer = buf;
}

void Figura::draw()
{
}
