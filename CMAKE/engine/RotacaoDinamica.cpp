#include "cmath"
#include "RotacaoDinamica.h"
#include "GL/glut.h"

RotacaoDinamica::RotacaoDinamica(){
	this->time = 0;
	this->axisX = 0;
	this->axisY = 0;
	this->axisZ = 0;
}


RotacaoDinamica::~RotacaoDinamica(){}

RotacaoDinamica::RotacaoDinamica(float time, float x, float y, float z){
	this->time = time;
	this->axisX = x;
	this->axisY = y;
	this->axisZ = z;
}

float RotacaoDinamica::getTime()
{
	return this->time;
}

float RotacaoDinamica::getAxisX() {
	return this->axisX;
}

float RotacaoDinamica::getAxisY() {
	return this->axisY;
}

float RotacaoDinamica::getAxisZ() {
	return this->axisZ;
}

void RotacaoDinamica::aplicaRotacao(float tempo){
	float angle = fmod((tempo * 360.0 / time), (360.0));
	glRotatef(angle, axisX, axisY, axisZ);
}
