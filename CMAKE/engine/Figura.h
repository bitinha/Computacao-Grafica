#include <vector>
#include "GL/glew.h"
#include "GL/glut.h"
#pragma once

using namespace std;

class Figura
{
public:
	vector<float> pontos;
	GLuint buffer;
	Figura();
	~Figura();
	vector<float> getPontos();
	void setPontos(vector<float> pontos);
	void setBuffer(GLuint buffer);
	virtual void draw();
};

