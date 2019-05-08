#include "FiguraDifusa.h"
//Eliminar a figuraCor a difusa e a Cor s�o as mesmas

FiguraDifusa::FiguraDifusa()
{
}

FiguraDifusa::FiguraDifusa(float r, float g, float b, float diffuse[3], float specular[3], float emissive[3], float ambient[3], vector<float> pontos, vector<float> normais)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->diffuse[0] = diffuse[0]; this->diffuse[1] = diffuse[1]; this->diffuse[2] = diffuse[2];
	this->specular[0] = specular[0]; this->specular[1] = specular[1]; this->specular[2] = specular[2];
	this->emissive[0] = emissive[0]; this->emissive[1] = emissive[1]; this->emissive[2] = emissive[2];
	this->ambient[0] = ambient[0]; this->ambient[1] = ambient[1]; this->ambient[2] = ambient[2];
	this->pontos = pontos;
	this->normais = normais;
}

FiguraDifusa::~FiguraDifusa()
{
}

float* FiguraDifusa::getDiffuse() {
	return this->diffuse;
}

void FiguraDifusa::setDiffuse(float* difuse) {
	this->diffuse[0] = difuse[0];
	this->diffuse[1] = difuse[1];
	this->diffuse[2] = difuse[2];
}

float* FiguraDifusa::getSpecular() {
	return this->specular;
}


void FiguraDifusa::setSpecular(float* specular) {
	this->specular[0] = specular[0];
	this->specular[1] = specular[1];
	this->specular[2] = specular[2];
}

float* FiguraDifusa::getEmissive(){
	return this->emissive;
}
	
void FiguraDifusa::setEmissive(float *emissive){
	this->emissive[0] = emissive[0];
	this->emissive[1] = emissive[1];
	this->emissive[2] = emissive[2];
}

float* FiguraDifusa::getAmbient() {
	return this->ambient;
}

void FiguraDifusa::setAmbient(float *ambient) {
	this->ambient[0] = ambient[0];
	this->ambient[1] = ambient[1];
	this->ambient[2] = ambient[2];
}

float FiguraDifusa::getR() {
	return this->r;
}

void FiguraDifusa::setR(float r) {
	this->r = r;
}

float FiguraDifusa::getG() {
	return this->g;
}

void FiguraDifusa::setG(float g) {
	this->g = g;
}

float FiguraDifusa::getB() {
	return this->b;
}

void FiguraDifusa::setB(float b) {
	this->b = b;
}

void FiguraDifusa::draw()
{	
	if (this->r >= 0 && this->r <= 1)
		glColor3f(this->r, this->g, this->b);
	if(this->diffuse[0] != -1)
		glMaterialfv(GL_FRONT, GL_DIFFUSE, this->diffuse);
	if(this->specular[0] != -1)
		glMaterialfv(GL_FRONT, GL_SPECULAR, this->specular);
	if (this->emissive[0] != -1)
		glMaterialfv(GL_FRONT, GL_EMISSION, this->emissive);
	if (this->ambient[0] != -1)
		glMaterialfv(GL_FRONT, GL_AMBIENT, this->ambient);
	
	glBindBuffer(GL_ARRAY_BUFFER, this->buffer);
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, this->bufferNormal);
	glNormalPointer(GL_FLOAT, 0, 0);
		
	glDrawArrays(GL_TRIANGLES, 0, this->pontos.size() / 3);
}