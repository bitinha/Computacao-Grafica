#include "GL/glut.h"
#pragma once
class RotacaoDinamica
{
public:
	float tempo, axisX, axisY, axisZ;
	RotacaoDinamica();
	~RotacaoDinamica();
	RotacaoDinamica(float time, float x, float y, float z);
	float getTempo();
	float getAxisX();
	float getAxisY();
	float getAxisZ();
	void draw(float tempo);
};

