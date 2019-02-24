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
