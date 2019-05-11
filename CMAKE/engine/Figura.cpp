#include "Figura.h"


Figura::Figura(char*nome, float diffuse[3], float specular[3], float emissive[3], float ambient[3], vector<float> pontos, vector<float> normais, vector<float> texCoord)
{
	this->diffuse[0] = diffuse[0]; this->diffuse[1] = diffuse[1]; this->diffuse[2] = diffuse[2]; this-> diffuse[3] = 1;
	this->specular[0] = specular[0]; this->specular[1] = specular[1]; this->specular[2] = specular[2]; this-> specular[3] = 1;
	this->emissive[0] = emissive[0]; this->emissive[1] = emissive[1]; this->emissive[2] = emissive[2]; this->emissive[3] = 1;
	this->ambient[0] = ambient[0]; this->ambient[1] = ambient[1]; this->ambient[2] = ambient[2]; this->ambient[3] = 1;
	this->pontos = pontos;
	this->normais = normais;
	this->textura = texCoord;
	this->nome = strdup(nome);
}

Figura::Figura()
{
}

Figura::~Figura()
{
}

vector<float> Figura::getPontos() {
	return this->pontos;
}

void Figura::setPontos(vector<float> pontos) {
	this->pontos = pontos;
}

void Figura::setBuffer(GLuint buf) {
	this->buffer = buf;
}


vector<float> Figura::getNormais(){
		return this->normais;
}
	
void Figura::setNormais(vector<float> normais){
		this->normais = normais;
}

GLuint Figura::getBufferNormal() {
	return this->bufferNormal;
}

void Figura::setBufferNormal(GLuint normais) {
	this->bufferNormal = normais;
}

vector<float> Figura::getTextura(){
	return this->textura;
}

void Figura::setTextura(vector<float> textura){
	this->textura = textura;
}
GLuint Figura::getBufferTextura(){
	return this->bufferTextura;
}
void Figura::setBufferTextura(GLuint bufferTextura){
	this->bufferTextura = bufferTextura;
}

float* Figura::getDiffuse() {
	return this->diffuse;
}

void Figura::setDiffuse(float* difuse) {
	this->diffuse[0] = difuse[0];
	this->diffuse[1] = difuse[1];
	this->diffuse[2] = difuse[2];
}

float* Figura::getSpecular() {
	return this->specular;
}


void Figura::setSpecular(float* specular) {
	this->specular[0] = specular[0];
	this->specular[1] = specular[1];
	this->specular[2] = specular[2];
}

float* Figura::getEmissive() {
	return this->emissive;
}

void Figura::setEmissive(float *emissive) {
	this->emissive[0] = emissive[0];
	this->emissive[1] = emissive[1];
	this->emissive[2] = emissive[2];
}

float* Figura::getAmbient() {
	return this->ambient;
}

void Figura::setAmbient(float *ambient) {
	this->ambient[0] = ambient[0];
	this->ambient[1] = ambient[1];
	this->ambient[2] = ambient[2];
}

char* Figura::getNome() {
	return this->nome;
}

void Figura::setNome(char* nome) {
	this->nome = nome;
}

GLuint Figura::getTexID() {
	return this->texID;
}

void Figura::setTexID(GLuint texID) {
	this->texID = texID;
}

void Figura::draw()
{
	if(this->nome != nullptr)
		glBindTexture(GL_TEXTURE_2D, this->texID);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, this->diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, this->ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, this->emissive);
	glMaterialfv(GL_FRONT, GL_AMBIENT, this->ambient);

	glBindBuffer(GL_ARRAY_BUFFER, this->buffer);
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, this->bufferNormal);
	glNormalPointer(GL_FLOAT, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, this->bufferTextura);
	glTexCoordPointer(2, GL_FLOAT, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, this->pontos.size() / 3);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Figura::generateTexturaFigura() {
	unsigned int t, tw, th;
	unsigned char *texData;
	unsigned int texID;


	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

	ilGenImages(1, &t);
	ilBindImage(t);
	ilLoadImage((ILstring)this->nome);
	tw = ilGetInteger(IL_IMAGE_WIDTH);
	th = ilGetInteger(IL_IMAGE_HEIGHT);
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	texData = ilGetData();

	glGenTextures(1, &texID);

	glBindTexture(GL_TEXTURE_2D, texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	this->texID = texID;
}