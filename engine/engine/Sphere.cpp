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

void Sphere::setRadius(float r) {
	this->radius = r;
}

int Sphere::getSlices() {
	return this->slices;
}

void Sphere::setSlices(int sl) {
	this->slices = sl;
}
int Sphere::getStacks() {
	return this->stacks;
}

void Sphere::setStacks(int st) {
	this->stacks = st;
}