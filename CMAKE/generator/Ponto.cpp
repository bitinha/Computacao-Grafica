#include "Ponto.h"

Ponto::Ponto()
{
}

Ponto::Ponto(float xc, float yc, float zc)
{
	this->x = xc;
	this->y = yc;
	this->z = zc;
}

Ponto::~Ponto()
{
}

float Ponto::getX() {
	return this->x;
}

float Ponto::getZ() {
	return this->y;
}

float Ponto::getY() {
	return this->z;
}
