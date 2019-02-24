#pragma once
class Box
{
	double x;
	double y;
	double z;
	double d;
public:
	Box();
	~Box();
	Box(double x, double y, double z, double d);
	double getX();
	double getY();
	double getZ();
	double getD();
	void setX();
	void setY();
	void setZ();
	void setD();
};