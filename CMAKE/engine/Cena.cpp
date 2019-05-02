#include "Cena.h"

Cena::Cena(){

}

Cena::Cena(vector<Grupo*> g, Luz* l) {
	this->grupos = g;
	this->luz = l;
}


Cena::~Cena() {

}

Luz* Cena::getLuz() {
	return this-> luz;
}

void Cena::setLuz(Luz* l) {
	this->luz = l;
}

vector<Grupo*> Cena::getGrupos() {
	return this->grupos;
}

void Cena::setGrupos(vector<Grupo*> g) {
	this->grupos = g;
}