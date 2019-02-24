#include "Plane.h"



Plane::Plane()
{
}


Plane::~Plane()
{
}

Plane::Plane(double x, double y) {
	this->x = x;
	this->z = z;
}

double Plane::getX() {
	return this->x;
}

double Plane::getZ() {
	return this->z;
}

void Plane::setX() {
	this->x = x;
}

void Plane::setZ() {
	this->z = z;
}