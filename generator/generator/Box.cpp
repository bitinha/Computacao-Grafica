#include "Box.h"

Box::Box()
{
}


Box::~Box()
{
}


Box::Box(double x, double y, double z, double d) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->d = d;
}

double Box::getX() {
	return this->x;
}

double Box::getY() {
	return this->y;
}

double Box::getZ() {
	return this->z;
}

double Box::getD() {
	return this->d;
}

void Box::setX() {
	this->x = x;
}

void Box::setY() {
	this->y = y;
}

void Box::setZ() {
	this->z = z;
}

void Box::setD() {
	this->d = d;
}
