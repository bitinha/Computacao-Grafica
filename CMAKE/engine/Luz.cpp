#include "Luz.h"

Luz::Luz() {

}

Luz::Luz(float p[3], float diff[3], float s[3], float a[3]){
	this->position[0] = p[0]; this->position[1] = p[1]; this->position[2] = p[2]; this->position[3] = 1;
	this->diffuse[0] = diff[0]; this->diffuse[1] = diff[1]; this->diffuse[2] = diff[2]; this-> diffuse[3] = 1;
	this->specular[0] = s[0]; this->specular[1] = s[1]; this->specular[2] = s[2]; this-> specular[3] = 1;
	this->ambient[0] = a[0]; this->ambient[1] = a[1]; this->ambient[2] = a[2]; this->ambient[3] = 1;
}

Luz::~Luz() {

}

float* Luz::getPosition() {
	return this->position;
}

void Luz::setPosition(float p[3]) {
	this->position[0] = p[0];
	this->position[1] = p[1];
	this->position[2] = p[2];
	this->position[3] = 1;
}

float* Luz::getDiffuse() {
	return this->diffuse;
}

void Luz::setDiffuse(float d[3]) {
	this->diffuse[0] = d[0];
	this->diffuse[1] = d[1];
	this->diffuse[2] = d[2];
	this->diffuse[3] = 1;
}

float* Luz::getSpecular() {
	return this->specular;
}

void Luz::setSpecular(float s[3]) {
	this->specular[0] = s[0];
	this->specular[1] = s[1];
	this->specular[2] = s[2];
	this->specular[3] = 1;
}

float* Luz::getAmbient() {
	return this->ambient;
}

void Luz::ilumina(int i) {
}


void Luz::setAmbient(float a[3]) {
	this->ambient[0] = a[0];
	this->ambient[1] = a[1];
	this->ambient[2] = a[2];
}