#include "RotacaoDinamica.h"



RotacaoDinamica::RotacaoDinamica(){}


RotacaoDinamica::~RotacaoDinamica(){}

RotacaoDinamica::RotacaoDinamica(float time, float x, float y, float z){
	this->tempo = time;
	this->axisX = x;
	this->axisY = y;
	this->axisZ = z;
}

void RotacaoDinamica::draw(float tempo){}
