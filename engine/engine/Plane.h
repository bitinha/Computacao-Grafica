#pragma once
#include "Shape.h"
class Plane: public Shape
{
	double x;
	double z;
public:
	Plane();
	~Plane();
	Plane(double x, double z);
	double getX();
	double getZ();
	void setX();
	void setZ();
};

