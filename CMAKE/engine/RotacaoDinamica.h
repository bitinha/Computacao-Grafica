#include "GL/glut.h"
#pragma once
class RotacaoDinamica
{
public:
	float time, axisX, axisY, axisZ;
	RotacaoDinamica();
	~RotacaoDinamica();
	RotacaoDinamica(float time, float x, float y, float z);
	float getTime();
	float getAxisX();
	float getAxisY();
	float getAxisZ();
	void aplicaRotacao(float t);
};

