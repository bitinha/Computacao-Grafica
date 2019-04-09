#pragma once
#include <vector>
#include "Transformacao.h"
class Translacao : public Transformacao
{
public: Translacao(float dx, float dy, float dz);
		Translacao();
	   ~Translacao();
	   void aplicaTransformacao();
};
