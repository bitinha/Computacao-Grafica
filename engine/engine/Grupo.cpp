#include "glew.h"
#include "Grupo.h"
#include "glut.h"


Grupo::Grupo(vector<Transformacao> trans, vector<float> p, vector<Grupo> grupos){
	this->transformacoes = trans;
	this->pontos = p;
	this->grupos = grupos;
}

Grupo::Grupo() {
	vector<Transformacao> trans;
	vector<float> p;
	vector<Grupo> g;
	this->transformacoes = trans;
	this->pontos = p;
	this->grupos = g;
}


Grupo::~Grupo()
{
}

vector<Transformacao> Grupo::getTranformacoes() {
	return this->transformacoes;
}

vector<float> Grupo::getPontos() {
	return this->pontos;
}

vector<Grupo> Grupo::getGrupos(){
	return this->grupos;
}

void Grupo::setTransformacoes(vector<Transformacao> trans) {
	this->transformacoes = trans;
}

void Grupo::setPontos(vector<float> p) {
	this->pontos = p;
}

void Grupo::setGrupos(vector<Grupo> g){
	this->grupos = g;
}

void Grupo::setBuffer(GLuint* buf) {
	this->buffer = *buf;
}

int Grupo::draw(GLuint buf[], int j) {
	glPushMatrix();
	for (vector<Transformacao>::iterator it = transformacoes.begin(); it != transformacoes.end(); it++) {
		(*it).aplicaTransformacao();
	}
	glBindBuffer(GL_ARRAY_BUFFER, buf[j]);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, pontos.size() / 3);

	j++;
	for (vector<Grupo>::iterator it = grupos.begin(); it != grupos.end(); it++) {
		j = (*it).draw(buf, j);
	}

	glPopMatrix();
	return j;
}

void Grupo::addPontos(vector<float> points) {
	this->pontos.insert(pontos.end(), points.begin(), points.end());
}

void Grupo::addGrupo(Grupo g) {
	this->grupos.push_back(g);
}

int Grupo::tamanhoGrupo() {
	int tam = 1;
	for (vector<Grupo>::iterator it = grupos.begin(); it != grupos.end(); it++) {
		tam += (*it).tamanhoGrupo();
	}
	return tam;
}