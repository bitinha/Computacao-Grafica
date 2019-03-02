#include "Vertice.h"



Vertice::Vertice()
{
}


Vertice::~Vertice()
{
}

Vertice::Vertice(float px, float py, float pz) {
	this->x = px;
	this->y = py;
	this->z = pz;
}

float Vertice::getX()
{
	return x;
}

float Vertice::getY()
{
	return y;
}

float Vertice::getZ()
{
	return z;
}
