#include "FiguraTextura.h"

FiguraTextura::FiguraTextura(char*nome, char*textData, vector<float> pontos, vector<float> normais, vector<float> textura){
	this->pontos = pontos;
	this->normais = normais;
	//this->textura = textura;
	this->nome = strdup(nome);
	this->textData = strdup(textData);
}

FiguraTextura::FiguraTextura(){

}

FiguraTextura::~FiguraTextura(){
}

void loadTexture() {
	/*
	unsigned int t, tw, th;
	unsigned char *texData;
	ilGenImages(1, &t);
	ilBindImage(t);
	ilLoadImage((ILstring)this->nome);
	tw = ilGetInteger(IL_IMAGE_WIDTH);
	th = ilGetInteger(IL_IMAGE_HEIGHT);
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	texData = ilGetData();

	glGenTextures(1, &texture); //Era uma variavel global no exe10

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);

	glGenerateMipmap(GL_TEXTURE_2D);
	*/
}

void init() {
	/*
	unsigned int ima[1]; // Colocar na classe
	
	ilInit();
	ilGenImages(1, ima); // ilGenImages(1, this->ima);
	ilBindImage(this->ima[0]);
	ilLoadImage((ILstring)this->nome);
	ilConvertImage(IL_LUMINANCE, IL_UNSIGNED_BYTE);

	imageWidth = ilGetInteger(IL_IMAGE_HEIGHT);
	imageData = ilGetData();

	prepareTerrain();

	loadTexture();

	glEnable(GL_TEXTURE_2D);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	*/
}

void FiguraTextura::draw() {
	/*
	float white[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);

	glBindTexture(GL_TEXTURE_2D, text);
	glBindBuffer(GL_ARRAY_BUFFER, this->buffers);
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, this->buffersNormal);
	glNormalPointer(GL_FLOAT, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, this->buffersTextura);
	glTexCoordPointer(2, GL_FLOAT, 0, 0);

	for (int i = 1; i < imageWidth - 2; i++) {
		glDrawArrays(GL_TRIANGLE_STRIP, (imageWidth - 2) * 2 * i, (imageWidth - 2) * 2);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	*/
}