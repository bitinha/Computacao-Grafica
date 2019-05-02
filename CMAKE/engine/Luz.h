#pragma once
class Luz
{
public: 
	float x, y, z;
	Luz();
	Luz(float x, float y, float z);
	~Luz();
	virtual float getX();
	float getY();
	float getZ();
};