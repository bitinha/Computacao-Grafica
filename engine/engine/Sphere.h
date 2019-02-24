#pragma once
#include "Shape.h"
class Sphere: public Shape 
{
	float radius;
	int slices, stacks;
public:
	Sphere();
	~Sphere();
	Sphere(float r, int sl, int st);
	float getRadius();
	void setRadius(float r);
	int getSlices();
	void setSlices(int sl);
	int getStacks();
	void setStacks(int st);
};

