#pragma once
class Sphere{
	float radius;
	int slices, stacks;
public:
	Sphere();
	~Sphere();
	Sphere(float r, int sl, int st);
	float getRadius();
};

