#include "Luz.h"

Luz::Luz() {

}

Luz::Luz(float x, float y, float z){
	this->x = x;
	this->y = y;
	this->z = z;
}

Luz::~Luz() {

}

float Luz::getX() {
	return this->x;
}

float Luz::getY() {
	return this->y;
}

float Luz::getZ() {
	return this->z;
}