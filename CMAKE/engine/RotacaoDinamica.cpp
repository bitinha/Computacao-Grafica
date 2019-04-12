#include "RotacaoDinamica.h"
#include "GL/glut.h"


RotacaoDinamica::RotacaoDinamica(){}


RotacaoDinamica::~RotacaoDinamica(){}

RotacaoDinamica::RotacaoDinamica(float time, float x, float y, float z){
	this->tempo = time;
	this->axisX = x;
	this->axisY = y;
	this->axisZ = z;
}

float RotacaoDinamica::getTempo()
{
	return this->tempo;
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

void RotacaoDinamica::draw(float tempo){}
