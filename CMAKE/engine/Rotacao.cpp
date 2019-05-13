#include <vector>
#include "GL/glut.h"
#include "Rotacao.h"

Rotacao::Rotacao(float a, float dx, float dy, float dz) {
	this->angle = a;
	this->x = dx;
	this->y = dy;
	this->z = dz;
}

Rotacao::Rotacao() {
}

Rotacao::~Rotacao()
{
}

float Rotacao::getAngle() {
	return this->angle;
}

void Rotacao::setAngle(float a) {
	this->angle = a;
}

void Rotacao::aplicaTransformacao(){
	glRotatef(angle, x, y, z);
}