#pragma once
#include <vector>
class Transformacao
{
public:float x, y, z;
	Transformacao();
	~Transformacao();
	float getX();
	float getY();
	float getZ();
	void setX(float dx);
	void setY(float dy);
	void setZ(float dz);
	virtual void aplicaTransformacao();
};
