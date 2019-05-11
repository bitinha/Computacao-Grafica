#pragma once
#include "Figura.h"
#include "GL/glew.h"
#include <vector>

using namespace std;

class FiguraTextura : public Figura
{
public:
	char * nome;
	GLuint texID;
	FiguraTextura(const char *nome, vector<float> pontos, vector<float> normais, vector<float> texCoord);
	~FiguraTextura();
	void setNome(char* nome);
	void setTexID(GLuint texID);
	void generateTexturaFigura();
	void draw();
};