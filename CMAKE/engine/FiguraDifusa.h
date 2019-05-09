#include "Figura.h"
#pragma once

using namespace std;

class FiguraDifusa: public Figura
{
public:
	float diffuse[4]; 
	float specular[4];
	float emissive[4];
	float ambient[4];
	FiguraDifusa(float diffuse[3], float specular[3], float emissive[3], float ambient[3], vector<float> pontos ,vector<float> normais/*, vector<float> textura*/);
	FiguraDifusa();
	~FiguraDifusa();
	float* getDiffuse();
	void setDiffuse(float *difuse);
	float* getSpecular();
	void setSpecular(float *specular);
	float* getEmissive();
	void setEmissive(float *emissive);
	float* getAmbient();
	void setAmbient(float *ambient);
	void draw();
};
