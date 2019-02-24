#include "Cone.h"



Cone::Cone()
{
}


Cone::~Cone()
{
}


Cone::Cone(double r, double h, int sl, int st)
{
	this->height = h;
	this->radius = r;
	this->slices = sl;
	this->stacks = st;
}

double Cone::getRadius() {
	return this->radius;
}

void Cone::setRadius(float r) {
	this->radius = r;
}

double Cone::getHeight() {
	return this->radius;
}

void Cone::setHeight(float r) {
	this->radius = r;
}

int Cone::getSlices() {
	return this->slices;
}

void Cone::setSlices(int sl) {
	this->slices = sl;
}
int Cone::getStacks() {
	return this->stacks;
}

void Cone::setStacks(int st) {
	this->stacks = st;
}