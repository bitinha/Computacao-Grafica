#include "Figura.h"
#pragma once

using namespace std;

class FiguraDifusa: public Figura
{
public:
	float r, g, b;
	float diffuse[4]; 
	float specular[4];
	float emissive[4];
	float ambient[4];
	FiguraDifusa(float r, float g, float b, float diffuse[3], float specular[3], float emissive[3], float ambient[3], vector<float> pontos ,vector<float> normais/*, vector<float> textura*/);
	FiguraDifusa();
	~FiguraDifusa();
	float getR();
	void setR(float r);
	float getG();
	void setG(float g);
	float getB();
	void setB(float b);
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
