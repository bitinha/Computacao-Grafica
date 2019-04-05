#include <vector>
#include "GL/glut.h"
#include "Scale.h"


Scale::Scale(float dx, float dy, float dz) {
	this->x = dx;
	this->y = dy;
	this->z = dz;
}


Scale::~Scale()
{
}

void Scale::aplicaTransformacao() {
	glScalef(this->x, this->y, this->z);
}