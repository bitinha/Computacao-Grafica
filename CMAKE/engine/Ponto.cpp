#include "Ponto.h"



Ponto::Ponto()
{
}

Ponto::Ponto(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Ponto::~Ponto()
{
}

float* Ponto::point2Array() {
	float p[3];
	p[0] = this->x;
	p[1] = this->y;
	p[2] = this->z;
	return p;
}
