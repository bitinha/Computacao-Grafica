#pragma once
#include "Figura.h"

using namespace std;

class FiguraCor : public Figura
{
public:
	float r, g, b;
	FiguraCor(float red, float green, float blue, vector<float> pontos);
	FiguraCor();
	~FiguraCor();
	void draw();
};