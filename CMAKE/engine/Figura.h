#include <vector>
#include "GL/glew.h"
#include "GL/glut.h"
#pragma once

using namespace std;

class Figura
{
public:
	vector<float> pontos;
	vector<float> normais;
	GLuint buffer;
	GLuint bufferNormal;
	Figura();
	~Figura();
	vector<float> getPontos();
	void setPontos(vector<float> pontos);
	void setBuffer(GLuint buffer);
	vector<float> getNormais();
	void setNormais(vector<float> normais);
	GLuint getBufferNormal();
	void setBufferNormal(GLuint bufferNormal);
	virtual void draw();
};

