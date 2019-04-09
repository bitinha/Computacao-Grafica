#include "Patches.h"


Patches::Patches()
{
}

Patches::~Patches()
{
}

void Patches::setNPatches(int nPatches) {
	this->nPatches = nPatches;
}

void Patches::setTesselation(int tesselation) {
	this->tesselation = tesselation;
}

void Patches::setNCP(int nCP) {
	this->nCP = nCP;
}

vector<Ponto*> Patches::generatePoints() {
	vector<Ponto*> ret;
	for (vector<Patch*>::iterator it = this->patches.begin(); it != patches.end(); it++) {
		(*it)->geraPontos(this->pontos,this->tesselation);
		vector<Ponto*> pts = (*it)->getPontos();
		for(vector<Ponto*>::iterator itPonto = pts.begin(); itPonto != pts.end(); itPonto++){
			ret.push_back((*itPonto));
		}
		
	}
	return ret;
}

void Patches::addPatch(Patch *p) {
	this->patches.push_back(p);

}

void Patches::addPonto(Ponto *ponto) {
	this->pontos.push_back(ponto);
}