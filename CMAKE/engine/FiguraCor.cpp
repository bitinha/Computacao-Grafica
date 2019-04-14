#include "FiguraCor.h"

FiguraCor::FiguraCor(float red, float green, float blue, vector<float> pontos){
	this->pontos = pontos;
	this->r = red;
	this->g = green;
	this->b = blue;
}

FiguraCor::FiguraCor(){
	this->r = 1;
	this->g = 1;
	this->b = 1;
}

FiguraCor::~FiguraCor(){
}

void FiguraCor::draw() {
	glColor3f(r, g, b);
	glBindBuffer(GL_ARRAY_BUFFER, this->buffer);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, this->pontos.size() / 3);
	glColor3f(1, 1, 1);
}