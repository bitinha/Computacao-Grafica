#include "TranslacaoDinamica.h"
#include "GL/glut.h"

TranslacaoDinamica::TranslacaoDinamica()
{
}

TranslacaoDinamica::TranslacaoDinamica(float time, vector<Ponto> pontos)
{
	this->time = time;
	this->pontos = pontos;
}

TranslacaoDinamica::~TranslacaoDinamica()
{
}

float TranslacaoDinamica::getTime()
{
	return this->time;
}

vector<Ponto> TranslacaoDinamica::getPontos() {
	return this->pontos;
}

void TranslacaoDinamica::cross(float *a, float *b, float *res) {

	res[0] = a[1] * b[2] - a[2] * b[1];
	res[1] = a[2] * b[0] - a[0] * b[2];
	res[2] = a[0] * b[1] - a[1] * b[0];
}

//Coloca entre 0 e 1
void TranslacaoDinamica::normalize(float *a) {

	float l = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
	a[0] = a[0] / l;
	a[1] = a[1] / l;
	a[2] = a[2] / l;
}

void TranslacaoDinamica::buildRotMatrix(float *x, float *y, float *z, float *m) {

	m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
	m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
	m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
	m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}

void TranslacaoDinamica::getCatmullRomPoint(float t, float *p0, float *p1, float *p2, float *p3, float *pos, float *deriv) {


	// catmull-rom matrix
	float m[4][4] = { {-0.5f,  1.5f, -1.5f,  0.5f},
						{ 1.0f, -2.5f,  2.0f, -0.5f},
						{-0.5f,  0.0f,  0.5f,  0.0f},
						{ 0.0f,  1.0f,  0.0f,  0.0f} };
	float A[3][4];
	// Compute A = M * P
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			A[i][j] = m[j][0] * p0[i] + m[j][1] * p1[i] + m[j][2] * p2[i] + m[j][3] * p3[i];
		}
	}
	// Compute pos = T * A

	for (int i = 0; i < 3; i++) {
		pos[i] = t * t*t*A[i][0] + t * t*A[i][1] + t * A[i][2] + A[i][3];
	}
	// compute deriv = T' * A
	for (int i = 0; i < 3; i++) {
		deriv[i] = 3 * t*t*A[i][0] + 2 * t*A[i][1] + A[i][2];
	}
}

// given  global t, returns the point in the curve
void TranslacaoDinamica::getGlobalCatmullRomPoint(float gt, float *pos, float *deriv, int size) {

	float t = (gt * size) / this->time; // this is the real global t
	int index = floor(t);  // which segment
	t = t - index; // where within  the segment

	// indices store the points
	int indices[4];
	indices[0] = (index + size - 1) % size;
	indices[1] = (indices[0] + 1) % size;
	indices[2] = (indices[1] + 1) % size;
	indices[3] = (indices[2] + 1) % size;

	getCatmullRomPoint(t, this->pontos[indices[0]].point2Array(), this->pontos[indices[1]].point2Array(),
		this->pontos[indices[2]].point2Array(), this->pontos[indices[3]].point2Array(), pos, deriv);
}


void TranslacaoDinamica::aplicaTranslacao(float t){
	float pos[3];
	float deriv[3];
	static float y[3] = { 0.0, 1.0, 0.0 }; // Será que o rotate e para aqui???
	float m[16];
	float z[3];

	getGlobalCatmullRomPoint(t, pos, deriv, this->pontos.size);
	glTranslatef(pos[0], pos[1], pos[2]);

	normalize(deriv);
	cross(deriv, y, z);
	normalize(z);
	cross(z, deriv, y);
	normalize(y);

	buildRotMatrix(deriv, y, z, m);
	glMultMatrixf(m);
}