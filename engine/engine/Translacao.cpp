#include <vector>
#include "glut.h"
#include "Translacao.h"

Translacao::Translacao(float dx, float dy, float dz) {
	this->x = dx;
	this->y = dy;
	this->z = dz;
}

Translacao::~Translacao()
{
}

void Translacao::aplicaTransformacao() {
	glPushMatrix();
	glTranslatef(this->x, this->y, this->z);
	glPopMatrix();
}