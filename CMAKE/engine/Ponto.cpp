#include "Ponto.h"
#include <stdlib.h>
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

float Ponto::getX() {
	return this->x;

}

float Ponto::getY() {
	return this->y;

}

float Ponto::getZ() {
	return this->z;

}

float* Ponto::point2Array() {
	float *p = (float *)malloc(sizeof(float) * 3);
	p[0] = this->x;
	p[1] = this->y;
	p[2] = this->z;
	return p;
}
