#pragma once
#include <vector>
class Transformacao
{
public:float x, y, z;
	Transformacao();
	~Transformacao();
	virtual float getX();
	virtual float getY();
	virtual float getZ();
	virtual void setX(float dx);
	virtual void setY(float dy);
	virtual void setZ(float dz);
};
