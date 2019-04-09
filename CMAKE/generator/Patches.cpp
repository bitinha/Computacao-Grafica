#include "Patches.h"


Patches::Patches()
{
}

Patches::~Patches()
{
}

void setNPatches(int nPatches) {
	this->nPatches = nPatches;
}

void setNCP(int nCP) {
	this->nCP = nCP;
}

vector<float> generatePoints() {
	
}

void write(FILE *filename) {

}

void addPatches(Patch p) {
	this->patches.push_back(p);

}

void addPontos(Ponto ponto) {
	this->pontos.push_back(ponto);
}