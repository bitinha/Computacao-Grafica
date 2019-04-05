#include <vector>
#include "GL/glut.h"
#include "Transformacao.h"

Transformacao::Transformacao(){
}


Transformacao::~Transformacao()
{
}

float Transformacao::getX() {
	return this->x;
}

void Transformacao::setX(float dx) {
	this->x = dx;
}

float Transformacao::getY() {
	return this->y;
}

void Transformacao::setY(float dy) {
	this->y = dy;
}

float Transformacao::getZ() {
	return this->z;
}

void Transformacao::setZ(float dz) {
	this->z = dz;
}

void Transformacao::aplicaTransformacao()
{
}
