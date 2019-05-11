#include <vector>
#include "GL/glew.h"
#include "GL/glut.h"
#include "IL/il.h"
#pragma once

using namespace std;

class Figura
{
public:
	vector<float> pontos;
	vector<float> normais;
	vector<float> textura;
	GLuint buffer;
	GLuint bufferNormal;
	GLuint bufferTextura;
	float diffuse[4];
	float specular[4];
	float emissive[4];
	float ambient[4];
	char * nome;
	GLuint texID;
	Figura(char*nome, float diffuse[3], float specular[3], float emissive[3], float ambient[3], vector<float> pontos, vector<float> normais, vector<float> texCoord);
	Figura();
	~Figura();
	float* getDiffuse();
	void setDiffuse(float *difuse);
	float* getSpecular();
	void setSpecular(float *specular);
	float* getEmissive();
	void setEmissive(float *emissive);
	float* getAmbient();
	void setAmbient(float *ambient);
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
	char* getNome();
	void setNome(char* nome);
	GLuint getTexID();
	void setTexID(GLuint texID);
	void draw();
	void generateTexturaFigura();
};

