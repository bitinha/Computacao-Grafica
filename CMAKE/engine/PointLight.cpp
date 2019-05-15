#include "PointLight.h"

PointLight::PointLight() {

}

PointLight::PointLight(float p[3], float diff[3], float s[3], float a[3], float atenuacao){
	this->position[0] = p[0]; this->position[1] = p[1]; this->position[2] = p[2]; this->position[3] = 1;
	this->diffuse[0] = diff[0]; this->diffuse[1] = diff[1]; this->diffuse[2] = diff[2]; this-> diffuse[3] = 1;
	this->specular[0] = s[0]; this->specular[1] = s[1]; this->specular[2] = s[2]; this-> specular[3] = 1;
	this->ambient[0] = a[0]; this->ambient[1] = a[1]; this->ambient[2] = a[2]; this->ambient[3] = 1;
	this->atenuacao = atenuacao;
}

PointLight::~PointLight() {

}

void PointLight::ilumina(int i) {
	glLightfv(GL_LIGHT0 + i, GL_POSITION, this->position);
	glLightfv(GL_LIGHT0 + i, GL_AMBIENT, this->ambient);
	glLightfv(GL_LIGHT0 + i, GL_SPECULAR, this->specular);
	glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, this->diffuse);

	glLightf(GL_LIGHT0 + i, GL_LINEAR_ATTENUATION, this->atenuacao);
	
}