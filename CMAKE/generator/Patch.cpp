#include "Patch.h"

Patch::Patch()
{
}

Patch::~Patch()
{
}

vector<int> Patch::getIndices() {
	return this->indices;
}

void Patch::setIndices(vector<int> indices) {
	this->indices = indices;
}

void Patch::addIndice(int indice) {
	this->indices.push_back(indice);
}