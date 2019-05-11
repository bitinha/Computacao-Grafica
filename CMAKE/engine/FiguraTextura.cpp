#include "FiguraTextura.h"

FiguraTextura::FiguraTextura(const char* nome,vector<float> pontos, vector<float> normais, vector<float> texCoord){
	this->nome = (char*)malloc(strlen(nome)* sizeof(char));
	int i = 0;
	for(; i < strlen(nome); i++)
		this->nome[i] = nome[i];
	this->nome[i] = '\0';
	this->pontos = pontos;
	this->normais = normais;
	this->textura = texCoord;
}


FiguraTextura::~FiguraTextura(){
}

void FiguraTextura::setNome(char* nome) {
	this->nome = nome;
}

void FiguraTextura::setTexID(GLuint texID) {
	this->texID = texID;
}

void FiguraTextura::generateTexturaFigura() {
	
	unsigned int t,tw,th;
	unsigned char *texData;
	unsigned int texID;

	
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

	ilGenImages(1,&t);
	ilBindImage(t);
	ilLoadImage((ILstring)this->nome);
	tw = ilGetInteger(IL_IMAGE_WIDTH);
	th = ilGetInteger(IL_IMAGE_HEIGHT);
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	texData = ilGetData();

	glGenTextures(1,&texID);
	
	glBindTexture(GL_TEXTURE_2D,texID);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_S,		GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_T,		GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_MAG_FILTER,   	GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	this->texID = texID;

}

void FiguraTextura::draw() {
		
	glBindTexture(GL_TEXTURE_2D, this->texID);

	glBindBuffer(GL_ARRAY_BUFFER, this->buffer);
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, this->bufferNormal);
	glNormalPointer(GL_FLOAT, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, this->bufferTextura);
	glTexCoordPointer(2, GL_FLOAT, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, this->pontos.size() / 3);
	
	glBindTexture(GL_TEXTURE_2D, 0);
	
}