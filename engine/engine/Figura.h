#pragma once
#include <vector>
#include "Transformacao.h"

using namespace std;

class Figura
{
public:vector<Transformacao> transformacoes;
	   char * file;
	Figura(vector<Transformacao> trans, char * f);
	~Figura();
	vector<Transformacao> getTransformacoes();
	void setTransformacoes(vector<Transformacao> trans);
	char* getFile();
	void setFile(char* f);
};