#pragma once
class Cone
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
};

