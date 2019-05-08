#include "Spot.h"

Spot::Spot() {

}

Spot::Spot(float p[3], float diff[3], float s[3], float a[3], float dir[3], GLfloat angle, GLfloat exponent, float atenuacao){
	this->position[0] = p[0]; this->position[1] = p[1]; this->position[2] = p[2]; this->position[3] = 1;
	this->diffuse[0] = diff[0]; this->diffuse[1] = diff[1]; this->diffuse[2] = diff[2]; this->diffuse[3] = 1;
	this->specular[0] = s[0]; this->specular[1] = s[1]; this->specular[2] = s[2]; this->specular[3] = 1;
	this->ambient[0] = a[0]; this->ambient[1] = a[1]; this->ambient[2] = a[2]; this->ambient[3] = 1;
	this->spotDirection[0] = dir[0]; this->spotDirection[1] = dir[1]; this->spotDirection[2] = dir[2];
	this->angle = angle;
	this->exponent = exponent;
	this->atenuacao = atenuacao;
}

Spot::~Spot() {

}

void Spot::ilumina(int i){
	glLightfv(i, GL_POSITION, this->position);
	glLightfv(i, GL_AMBIENT, this->ambient);
	glLightfv(i, GL_DIFFUSE, this->diffuse);
	glLightfv(i, GL_SPECULAR, this->specular);

	glLightfv(i, GL_SPOT_DIRECTION, this->spotDirection);
	
	glLightfv(i, GL_SPOT_CUTOFF, &this->angle);
	glLightfv(i, GL_SPOT_EXPONENT, &this->exponent);
	glLightf(i, GL_QUADRATIC_ATTENUATION, this->atenuacao);
}