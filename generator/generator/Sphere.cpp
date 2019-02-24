#include "Sphere.h"



Sphere::Sphere()
{
}


Sphere::~Sphere()
{
}

Sphere::Sphere(float r, int sl, int st){
	this->radius = r;
	this->slices = sl;
	this->stacks = st;
}

float Sphere::getRadius() {
	return this->radius;
}
