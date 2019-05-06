#include "Ponto2D.h"

Ponto2D::Ponto2D()
{
}

Ponto2D::Ponto2D(float xc, float yc)
{
	this->x = xc;
	this->y = yc;
}

Ponto2D::~Ponto2D()
{
}

float Ponto2D::getX() {
	return this->x;
}

float Ponto2D::getY() {
	return this->y;
}
