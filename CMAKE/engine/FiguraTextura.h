#pragma once
#include "Figura.h"
#include "GL/glew.h"

using namespace std;

class FiguraTextura : public Figura
{
public:
	char *nome, *textData;
	//unsigned int ima[1], text;
	FiguraTextura(char* name, char* textData, vector<float> pontos, vector<float> normais, vector<float> textura);
	FiguraTextura();
	~FiguraTextura();
	void loadTexture();
	void init();
	void draw();
};