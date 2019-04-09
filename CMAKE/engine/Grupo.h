#include <vector>
#include "Transformacao.h"
#include "GL/glut.h"
#include "RotacaoDinamica.h"
#include "TranslacaoDinamica.h"
#pragma once
using namespace std;
class Grupo
{
public: vector<Transformacao*> transformacoes;
		TranslacaoDinamica translacao;
		RotacaoDinamica rotacao;
		vector<float> pontos;
		vector<Grupo*> grupos;
		GLuint buffer;

		Grupo(vector<Transformacao*> trans, vector<float> p, vector<Grupo*> grupos, TranslacaoDinamica translacao, RotacaoDinamica rotacao);
		Grupo();
		~Grupo();
		vector<Transformacao*> getTranformacoes();
		vector<float> getPontos();
		vector<Grupo*> getGrupos();
		void setTransformacoes(vector<Transformacao*> trans);
		void setPontos(vector<float> p);
		void setGrupos(vector<Grupo*> g);
		void setBuffer(GLuint buf);
		void setTransDinamica(TranslacaoDinamica translacao);
		void setRotacaoDinamica(RotacaoDinamica rotacao); 
		void addPontos(vector<float> pontos);
		void addGrupo(Grupo *g);
		int tamanhoGrupo();
		void draw();
};