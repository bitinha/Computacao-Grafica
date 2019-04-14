#include "Grupo.h"

using namespace std;

Grupo::Grupo(vector<Transformacao*> trans, vector<Figura*> p, vector<Grupo*> grupos, TranslacaoDinamica translacao, RotacaoDinamica rotacao){
	this->transformacoes = trans;
	this->figuras = p;
	this->grupos = grupos;
	this->translacao = translacao;
	this->rotacao = rotacao;
}

Grupo::Grupo() {
	vector<Transformacao*> trans;
	RotacaoDinamica rotacao;
	TranslacaoDinamica translacao;
	vector<Figura*> p;
	vector<Grupo*> g;
	this->transformacoes = trans;
	this->rotacao = rotacao;
	this->translacao = translacao;
	this->figuras = p;
	this->grupos = g;
}

Grupo::~Grupo()
{
}

vector<Transformacao*> Grupo::getTranformacoes() {
	return this->transformacoes;
}

vector<Figura*> Grupo::getFiguras() {
	return this->figuras;
}

vector<Grupo*> Grupo::getGrupos(){
	return this->grupos;
}

void Grupo::setTransformacoes(vector<Transformacao*> trans) {
	this->transformacoes = trans;
}

void Grupo::setFiguras(vector<Figura*> p) {
	this->figuras = p;
}

void Grupo::setGrupos(vector<Grupo*> g){
	this->grupos = g;
}

TranslacaoDinamica Grupo::getTransDinamica(){
	return this->translacao;
}

void Grupo::setTransDinamica(TranslacaoDinamica transl) {
	this->translacao = transl;
}

void Grupo::setRotacaoDinamica(RotacaoDinamica rotacao) {
	this->rotacao = rotacao;
}

void Grupo::addFigura(Figura* points) {
	this->figuras.push_back(points);
}

void Grupo::addGrupo(Grupo *g) {
	this->grupos.push_back(g);
}

int Grupo::tamanhoGrupo() {
	int tam = figuras.size();
	for (vector<Grupo*>::iterator it = grupos.begin(); it != grupos.end(); it++) {
		tam += (*it)->tamanhoGrupo();
	}
	return tam;
}

void Grupo::draw(float time) {
	glPushMatrix();
	for (vector<Transformacao*>::iterator it = transformacoes.begin(); it != transformacoes.end(); it++) {
		(*it)->aplicaTransformacao();
	}
	if (translacao.getPontos().size() >= 4) {
		translacao.aplicaTranslacao(time);
	}
	if (rotacao.getTime() != 0) 
		rotacao.aplicaRotacao(time);

	for (vector<Figura*>::iterator it = figuras.begin(); it != figuras.end(); it++) {
		(*it)->draw();
	}

	for (vector<Grupo*>::iterator it = grupos.begin(); it != grupos.end(); it++) {
		(*it)->draw(time);
	}
	glPopMatrix();
}