#pragma once
class Ponto
{
public:float x, y, z;
	Ponto();
	Ponto(float x, float y, float z);
	~Ponto();
	float* point2Array();
};