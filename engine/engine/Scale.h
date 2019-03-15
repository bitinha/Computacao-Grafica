#pragma once
#include <vector>
#include "Transformacao.h"
class Scale : public Transformacao
{
public:
	Scale(float dx, float dy, float dz);
	~Scale();
	void aplicaTransformacao();
};