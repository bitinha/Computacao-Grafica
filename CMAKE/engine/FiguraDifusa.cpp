#include "FiguraDifusa.h"
//Eliminar a figuraCor a difusa e a Cor são as mesmas

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

void FiguraDifusa::draw()
{	
	glColor3f(this->r, this->g, this->b);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, this->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, this->specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, this->emissive);
	glBindBuffer(GL_ARRAY_BUFFER, this->buffer);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, this->pontos.size() / 3);
	glColor3f(1, 1, 1);
}
