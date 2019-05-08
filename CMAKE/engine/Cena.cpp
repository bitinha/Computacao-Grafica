#include "Cena.h"

Cena::Cena(){

}

Cena::Cena(vector<Grupo*> g, vector<Luz*> l) {
	this->grupos = g;
	this->luz = l;
}


Cena::~Cena() {

}

vector<Luz*> Cena::getLuz() {
	return this-> luz;
}

void Cena::setLuz(vector<Luz*> l) {
	this->luz = l;
}

vector<Grupo*> Cena::getGrupos() {
	return this->grupos;
}

void Cena::setGrupos(vector<Grupo*> g) {
	this->grupos = g;
}

void Cena::ilumina() {
	int tam = this->luz.size();
	for (int i = 0; i < tam; i++) {

	}
}