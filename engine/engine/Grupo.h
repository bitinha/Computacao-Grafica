#include <vector>
#include "Transformacao.h"
#include "glut.h"
#pragma once
using namespace std;
class Grupo
{
public: vector<Transformacao> transformacoes;
		vector<float> pontos;
		vector<Grupo> grupos;
		GLuint buffer;
		Grupo(vector<Transformacao> trans, vector<float> p, vector<Grupo> grupos);
		Grupo();
		~Grupo();
		vector<Transformacao> getTranformacoes();
		vector<float> getPontos();
		vector<Grupo> getGrupos();
		void setTransformacoes(vector<Transformacao> trans);
		void setPontos(vector<float> p);
		void setGrupos(vector<Grupo> g);
		void setBuffer(GLuint* buf);
		void addPontos(vector<float> pontos);
		void addGrupo(Grupo g);
		int tamanhoGrupo();
		int draw(GLuint buf[], int j);
};