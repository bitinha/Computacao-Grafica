#include "Figura.h"
#include "Transformacao.h"
#include "RotacaoDinamica.h"
#include "TranslacaoDinamica.h"
#pragma once
using namespace std;
class Grupo
{
public: vector<Transformacao*> transformacoes;
		TranslacaoDinamica translacao;
		RotacaoDinamica rotacao;
		vector<Figura*> figuras;
		vector<Grupo*> grupos;

		Grupo(vector<Transformacao*> trans, vector<Figura*> p, vector<Grupo*> grupos, TranslacaoDinamica translacao, RotacaoDinamica rotacao);
		Grupo();
		~Grupo();
		vector<Transformacao*> getTranformacoes();
		vector<Figura*> getFiguras();
		vector<Grupo*> getGrupos();
		void setTransformacoes(vector<Transformacao*> trans);
		void setFiguras(vector<Figura*> p);
		void setGrupos(vector<Grupo*> g);
		TranslacaoDinamica getTransDinamica();
		void setTransDinamica(TranslacaoDinamica translacao);
		void setRotacaoDinamica(RotacaoDinamica rotacao); 
		void addFigura(Figura* pontos);
		void addGrupo(Grupo *g);
		int tamanhoGrupo();
		void draw(float time);
};