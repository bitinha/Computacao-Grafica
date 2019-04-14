#pragma once
#include "Ponto.h"
#include <vector>

using namespace std;

class TranslacaoDinamica
{
public: float time;
		vector<Ponto> pontos;
	TranslacaoDinamica();
	TranslacaoDinamica(float time, vector<Ponto> pontos);
	~TranslacaoDinamica();	
	float getTime();
	vector<Ponto> getPontos();
	void getCatmullRomPoint(float t, float p0[3], float p1[3], float p2[3], float p3[3], float *pos, float *deriv);
	void getGlobalCatmullRomPoint(float gt, float *pos, float *deriv, int size);
	void aplicaTranslacao(float t);
	void cross(float *a , float *b, float *res);
	void normalize(float *a);
	void buildRotMatrix(float *x, float *y, float *z, float *m);
};