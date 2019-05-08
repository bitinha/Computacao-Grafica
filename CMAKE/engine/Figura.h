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
	//vector<float> textura;
	GLuint buffer;
	GLuint bufferNormal;
	//GLuint bufferTextura;
	Figura();
	~Figura();
	vector<float> getPontos();
	void setPontos(vector<float> pontos);
	void setBuffer(GLuint buffer);
	vector<float> getNormais();
	void setNormais(vector<float> normais);
	GLuint getBufferNormal();
	void setBufferNormal(GLuint bufferNormal);
	vector<float> getTextura();
	void setTextura(vector<float> textura);
	GLuint getBufferTextura();
	void setBufferTextura(GLuint bufferTextura);
	virtual void draw();
};

