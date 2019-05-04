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


vector<float> Figura::getNormais(){
		return this->normais;
}
	
void Figura::setNormais(vector<float> normais){
		this->normais = normais;
}

GLuint Figura::getBufferNormal() {
	return this->bufferNormal;
}

void Figura::setBufferNormal(GLuint normais) {
	this->bufferNormal = normais;
}

void Figura::draw()
{
}
