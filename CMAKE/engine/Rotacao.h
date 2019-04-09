#pragma once
#include <vector>
#include "Transformacao.h"

class Rotacao : public Transformacao
{
public:float angle;
	Rotacao(float a, float dx, float dy, float dz);
	Rotacao();
	~Rotacao();
	float getAngle();
	void setAngle(float a);
	void aplicaTransformacao(float *deriv);
};