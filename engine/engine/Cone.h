#pragma once
#include "Shape.h"
class Cone: public Shape
{
	double radius;
	double height;
	int slices;
	int stacks;
public:
	Cone();
	~Cone();
	Cone(double r, double h, int sl, int st);
	double getRadius();
	void setRadius(float r);
	double getHeight();
	void setHeight(float r);
	int getSlices();
	void setSlices(int sl);
	int getStacks();
	void setStacks(int st);
};

