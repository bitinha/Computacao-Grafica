#define _USE_MATH_DEFINES
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>
#include <math.h>
#include "Patches.h"
#include "Patch.h"
#include "Ponto.h"

float pi = M_PI;

using namespace std;

Patch* readPatch(FILE *file){
	Patch *p = new Patch();
	int ind;
	for(int i = 0; i < 15; i++){
		fscanf_s(file, "%d, ", &ind);
		p->addIndice(ind);
	}
	fscanf_s(file, "%d\n", &ind);
	p->addIndice(ind);
	return p;
}

Ponto* readPoint(FILE *file){

	float x,y,z;

	fscanf(file, " %f, %f, %f\n", &x, &y, &z);
	Ponto *p = new Ponto(x,y,z);

	return p;
}

void cross(float *a, float *b, float *res) {

	res[0] = a[1] * b[2] - a[2] * b[1];
	res[1] = a[2] * b[0] - a[0] * b[2];
	res[2] = a[0] * b[1] - a[1] * b[0];
}

void normalize(float *a) {

	float l = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
	a[0] = a[0] / l;
	a[1] = a[1] / l;
	a[2] = a[2] / l;
}


Ponto normal(Ponto l1, Ponto l2, Ponto c1, Ponto c2) {
	float v1[3] = { l1.getX() - l2.getX(), l1.getY() - l2.getY(), l1.getZ() - l2.getZ() };
	float v2[3] = { c1.getX() - c2.getX(), c1.getY() - c2.getY(), c1.getZ() - c2.getZ() };
	float res[3];

	cross(v1, v2, res);
	normalize(res);
	Ponto p = Ponto(res[0], res[1], res[2]);

	return p;
}


vector<Ponto> generateNormais(vector<Ponto*> pontos, int tess, int np) {
	vector<Ponto> normais;
	int n = 0;
	//para cada comentario acrescentar 6 pontos
	for (int k = 0; k < np; k++) {
		// Fazer para o triangulo inferior esquerda
		Ponto p = normal(*pontos[n], *pontos[n + 5], *pontos[n], *pontos[n + 1]);
		normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
		n++;

		p = normal(*pontos[n], *pontos[n + 3], *pontos[n - 1], *pontos[n + 6]);
		normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
		n++;

		p = normal(*pontos[n - 1], *pontos[n + 6 * tess], *pontos[n + 3], *pontos[n + 6]);
		normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
		n++;

		p = normal(*pontos[n], *pontos[n + 2], *pontos[n], *pontos[n - 2]);
		normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
		n++;

		p = normal(*pontos[n - 3], *pontos[n + 6 * tess], *pontos[n + 1], *pontos[n + 6]);
		normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
		n++;

		p = normal(*pontos[n - 2], *pontos[n + 6*tess], *pontos[n], *pontos[n + 6]);
		normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
		n++;
		//Fazer para os do meio da primeira linha
		for (int i = 1; i < tess - 1; i++) {
			p = normal(*pontos[n], *pontos[n + 5], *pontos[n - 6], *pontos[n + 6]);
			normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
			n++;

			p = normal(*pontos[n], *pontos[n + 1], *pontos[n - 1], *pontos[n + 6]);
			normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
			n++;

			p = normal(*pontos[n - 1], *pontos[n + 6 * tess], *pontos[n + 3], *pontos[n + 6]);
			normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
			n++;

			p = normal(*pontos[n], *pontos[n + 2], *pontos[n - 6], *pontos[n - 2]);
			normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
			n++;

			p = normal(*pontos[n - 3], *pontos[n + 6 * tess], *pontos[n + 1], *pontos[n + 6]);
			normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
			n++;

			p = normal(*pontos[n - 2], *pontos[n + 6 * tess], *pontos[n - 6], *pontos[n + 6]);
			normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
			n++;
		}
		//Fazer para o canto da inferior direita
			p = normal(*pontos[n], *pontos[n + 5], *pontos[n - 6], *pontos[n + 6]);
			normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
			n++;

			p = normal(*pontos[n], *pontos[n + 1], *pontos[n - 1], *pontos[n]);
			normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
			n++;

			p = normal(*pontos[n - 1], *pontos[n + 6 * tess], *pontos[n + 3], *pontos[n]);
			normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
			n++;

			p = normal(*pontos[n], *pontos[n + 2], *pontos[n - 6], *pontos[n - 2]);
			normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
			n++;

			p = normal(*pontos[n - 3], *pontos[n + 6 * tess], *pontos[n + 1], *pontos[n]);
			normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
			n++;

			p = normal(*pontos[n - 2], *pontos[n + 6 * tess], *pontos[n - 6], *pontos[n - 1]);
			normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
			n++;
		//Fazer para as linhas do meio
		for (int i = 1; i < tess - 1; i++) {
			//Fazer para a primeira coluna
			p = normal(*pontos[n - 6 * tess], *pontos[n + 5], *pontos[n], *pontos[n + 1]);
			normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
			n++;

			p = normal(*pontos[n - 6 * tess], *pontos[n + 1], *pontos[n - 1], *pontos[n + 6]);
			normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
			n++;

			p = normal(*pontos[n - 1], *pontos[n + 6 * tess], *pontos[n + 3], *pontos[n + 6]);
			normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
			n++;

			p = normal(*pontos[n - 6 * tess], *pontos[n + 2], *pontos[n], *pontos[n - 2]);
			normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
			n++;

			p = normal(*pontos[n - 3], *pontos[n + 6 * tess], *pontos[n + 1], *pontos[n + 6]);
			normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
			n++;

			p = normal(*pontos[n - 2], *pontos[n + 6 * tess], *pontos[n], *pontos[n - 1]);
			normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
			n++;
			//Fazer para as colunas do meio
			for (int j = 1; j < tess - 1; j++) {
				p = normal(*pontos[n - 6 * tess], *pontos[n + 5], *pontos[n - 6], *pontos[n + 1]);
				normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
				n++;

				p = normal(*pontos[n - 6 * tess], *pontos[n + 1], *pontos[n - 1], *pontos[n + 6]);
				normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
				n++;

				p = normal(*pontos[n - 1], *pontos[n + 6 * tess], *pontos[n + 3], *pontos[n + 6]);
				normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
				n++;

				p = normal(*pontos[n - 6 * tess], *pontos[n + 2], *pontos[n - 6], *pontos[n - 2]);
				normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
				n++;

				p = normal(*pontos[n - 3], *pontos[n + 6 * tess], *pontos[n + 1], *pontos[n + 6]);
				normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
				n++;

				p = normal(*pontos[n - 2], *pontos[n + 6 * tess], *pontos[n - 6], *pontos[n - 1]);
				normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
				n++;
			}
			//Fazer para a ultima coluna
			p = normal(*pontos[n - 6 * tess], *pontos[n + 5], *pontos[n - 6], *pontos[n + 1]);
			normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
			n++;

			p = normal(*pontos[n - 6 * tess], *pontos[n + 1], *pontos[n], *pontos[n + 1]);
			normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
			n++;

			p = normal(*pontos[n - 1], *pontos[n + 6 * tess], *pontos[n + 3], *pontos[n]);
			normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
			n++;

			p = normal(*pontos[n - 6 * tess], *pontos[n + 2], *pontos[n - 6], *pontos[n - 2]);
			normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
			n++;

			p = normal(*pontos[n - 3], *pontos[n + 6 * tess], *pontos[n + 1], *pontos[n]);
			normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
			n++;

			p = normal(*pontos[n - 2], *pontos[n + 6 * tess], *pontos[n - 6], *pontos[n - 1]);
			normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
			n++;
		}
		//Fazer para o canto superior esquerdo
		p = normal(*pontos[n - 6 * tess], *pontos[n + 5], *pontos[n], *pontos[n + 1]);
		normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
		n++;

		p = normal(*pontos[n - 6 * tess], *pontos[n + 1], *pontos[n - 1], *pontos[n + 6]);
		normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
		n++;

		p = normal(*pontos[n - 1], *pontos[n], *pontos[n + 3], *pontos[n + 6]);
		normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
		n++;

		p = normal(*pontos[n - 6 * tess], *pontos[n + 2], *pontos[n], *pontos[n - 2]);
		normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
		n++;

		p = normal(*pontos[n - 3], *pontos[n], *pontos[n + 1], *pontos[n + 6]);
		normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
		n++;

		p = normal(*pontos[n - 2], *pontos[n], *pontos[n], *pontos[n - 1]);
		normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
		n++;
		//Fazer para as colunas do meio
		for (int i = 1; i < tess - 1; i++) {
			p = normal(*pontos[n - 6 * tess], *pontos[n + 5], *pontos[n - 6], *pontos[n + 1]);
			normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
			n++;

			p = normal(*pontos[n - 6 * tess], *pontos[n + 1], *pontos[n - 1], *pontos[n + 6]);
			normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
			n++;

			p = normal(*pontos[n - 1], *pontos[n], *pontos[n + 3], *pontos[n + 6]);
			normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
			n++;

			p = normal(*pontos[n - 6 * tess], *pontos[n + 2], *pontos[n - 6], *pontos[n - 2]);
			normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
			n++;

			p = normal(*pontos[n - 3], *pontos[n], *pontos[n + 1], *pontos[n + 6]);
			normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
			n++;

			p = normal(*pontos[n - 2], *pontos[n], *pontos[n - 6], *pontos[n - 1]);
			normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
			n++;
		}
		//Fazer para o canto superior direito
		p = normal(*pontos[n - 6 * tess], *pontos[n + 5], *pontos[n - 6], *pontos[n + 1]);
		normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
		n++;

		p = normal(*pontos[n - 6 * tess], *pontos[n + 1], *pontos[n - 1], *pontos[n]);
		normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
		n++;

		p = normal(*pontos[n - 1], *pontos[n], *pontos[n + 3], *pontos[n]);
		normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
		n++;

		p = normal(*pontos[n - 6 * tess], *pontos[n + 2], *pontos[n - 6], *pontos[n - 2]);
		normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
		n++;

		p = normal(*pontos[n - 3], *pontos[n], *pontos[n + 1], *pontos[n]);
		normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
		n++;

		p = normal(*pontos[n - 2], *pontos[n], *pontos[n - 6], *pontos[n - 1]);
		normais.push_back(Ponto(p.getX(), p.getY(), p.getZ()));
		n++;
	}
	n = n;
	return normais;
}

void writePatchFile(const char *inputFile, const char *tesselation,string outputFile){
	Patches *ps = new Patches();
	FILE *pfile;
	errno_t erro = fopen_s(&pfile, inputFile, "r");
	
	if (erro == 0) {
		// LÊ PONTOS
		int tess = atoi(tesselation);
		ps->setTesselation(tess);
		int np;
		fscanf_s(pfile, "%d\n", &np);
		ps->setNPatches(np);
		
		for(int i = 0; i< np; i++){
			Patch* p = readPatch(pfile);
			ps->addPatch(p);
		}
		
		int nCP;
		ps->setNCP(fscanf_s(pfile, "%d\n", &nCP));
		
		for(int i = 0; i< nCP; i++){
			Ponto* p = readPoint(pfile);
			ps->addPonto(p);
		}
		
		fclose(pfile);
		
		//GERA PONTOS
		vector<Ponto*> pts = ps->generatePoints();
		vector<Ponto> nrm = generateNormais(pts, tess, np);

		//ESCREVE PONTOS
		
		fstream file; //Nome do ficheiro no qual vão ser escritos os vértices
		file.open(outputFile, ios::out);
		if (file.is_open()) {
			vector<Ponto*>::iterator it = pts.begin();
			vector<Ponto>::iterator itN = nrm.begin();
			for (; it != pts.end(); it++) {
				file << " " << (*it)->getX() << " " << (*it)->getY() << " " << (*it)->getZ() << "\n";
				file << " " << (itN)->getX() << " " << (itN)->getY() << " " << (itN)->getZ() << "\n";
				itN++;
			}
			
		}
		else printf("File not opened\n");
		file.close();
		
	}
}

/**
\brief Função que escreve os vértices de uma esfera num ficheiro
@param r Raio da esfera
@param sl Número de fatias da esfera
@param st Número de camadas da esfera
@param name Ficheiro onde escrever os vértices
*/
void writeSphereFile(const char* r, const char* sl, const char* st, string name) {
	fstream file;
	file.open(name, ios::out);
	if (file.is_open()) {
		float a = 0;
		float radius = atof(r);
		float slices = atof(sl);
		float stacks = atof(st);
		float p[3];
		for (int i = 0; i < slices; i++) {
			a = i * 2 * pi / slices;
			float gama = (i + 1)* 2 * pi / slices;
			float b = (pi / 2) - (pi / stacks);
			
			file << " " << 0 << " " << radius << " " << 0 << "\n";
			file << " " << 0 << " " << 1 << " " << 0 << "\n"; //Normal
			
			file << " " << radius * cos(b) * sin(a) << " " << radius * sin(b) << " " << radius * cos(b) * cos(a) << "\n";
			p[0] = cos(b) * sin(a); p[1] = sin(b); p[2] = cos(b) * cos(a); normalize(p);
			file << " " << p[0] << " " << p[1] << " " << p[2] << "\n"; //Normal
			
			file << " " << radius * cos(b) * sin(gama) << " " << radius * sin(b) << " " << radius * cos(b) * cos(gama) << "\n";
			p[0] = cos(b) * sin(gama); p[1] = sin(b); p[2] = cos(b) * cos(gama); normalize(p);
			file << " " << p[0] << " " << p[1] << " " << p[2] << "\n"; //Normal

			b = -b;

			file << " " << 0 << " " << -radius << " " << 0 << "\n";
			file << " " << 0 << " " << -1 << " " << 0 << "\n"; //Normal

			file << " " << radius * cos(b) * sin(gama) << " " << radius * sin(b) << " " << radius * cos(b) * cos(gama) << "\n";
			p[0] = cos(b) * sin(gama); p[1] = sin(b); p[2] = cos(b) * cos(gama); normalize(p);
			file << " " << p[0] << " " << p[1] << " " << p[2] << "\n"; //Normal
			
			file << " " << radius * cos(b) * sin(a) << " " << radius * sin(b) << " " << radius * cos(b) * cos(a) << "\n";
			p[0] = cos(b) * sin(a); p[1] = sin(b); p[2] = cos(b) * cos(a); normalize(p);
			file << " " << p[0] << " " << p[1] << " " << p[2] << "\n"; //Normal

			for (int j = 1; j < stacks - 1; j++) {
				b = pi / 2 - (j * pi / (stacks));
				float teta = pi / 2 - ((j + 1) * pi / (stacks));

				file << " " << radius * cos(b) * sin(a) << " " << radius * sin(b) << " " << radius * cos(b) * cos(a) << "\n";
				p[0] = cos(b) * sin(a); p[1] = sin(b); p[2] = cos(b) * cos(a); normalize(p);
				file << " " << p[0] << " " << p[1] << " " << p[2] << "\n"; //Normal

				file << " " << radius * cos(teta) * sin(a) << " " << radius * sin(teta) << " " << radius * cos(teta) * cos(a) << "\n";
				p[0] = cos(teta) * sin(a), p[1] = sin(teta); p[2] = cos(a) * cos(teta); normalize(p);
				file << " " << p[0] << " " << p[1] << " " << p[2] << "\n"; //Normal
				
				file << " " << radius * cos(b) * sin(gama) << " " << radius * sin(b) << " " << radius * cos(b) * cos(gama) << "\n";
				p[0] = cos(b) * sin(gama); p[1] = sin(b); p[2] = cos(b) * cos(gama); normalize(p);
				file << " " << p[0] << " " << p[1] << " " << p[2] << "\n"; //Normal

				file << " " << radius * cos(b) * sin(gama) << " " << radius * sin(b) << " " << radius * cos(b) * cos(gama) << "\n";
				p[0] = cos(b) * sin(gama); p[1] = sin(b); p[2] = cos(b) * cos(gama); normalize(p);
				file << " " << p[0] << " " << p[1] << " " << p[2] << "\n"; //Normal
				
				file << " " << radius * cos(teta) * sin(a) << " " << radius * sin(teta) << " " << radius * cos(teta) * cos(a) << "\n";
				p[0] = cos(teta) * sin(a); p[1] = sin(teta); p[2] = cos(teta) * cos(a); normalize(p);
				file << " " << p[0] << " " << p[1] << " " << p[2] << "\n"; //Normal
				
				file << " " << radius * cos(teta) * sin(gama) << " " << radius * sin(teta) << " " << radius * cos(teta) * cos(gama) << "\n";
				p[0] = cos(teta) * sin(gama); p[1] = sin(teta); p[2] = cos(teta) * cos(gama); normalize(p);
				file << " " << p[0] << " " << p[1] << " " << p[2] << "\n"; //Normal

			}
		}
	}
	else printf("File not opened\n");
	file.close();
}

/**
\brief Função que escreve os vértices de um plano num ficheiro
@param x Comprimento do plano
@param name Ficheiro onde escrever os vértices
*/
void writePlaneFile(const char* x, string name) {
	fstream file; //Nome do ficheiro no qual vão ser escritos os vértices
	file.open(name, ios::out);
	if (file.is_open()) {
		float size = atof(x) / 2; //Módulo das coordenadas x, z dos vertices dos triangulos
		file << " " << -size << " " << 0 << " " << - size << "\n"; //Ponto A
		file << " " << 0 << " " << 1 << " " << 0 << "\n"; //Normal A
		file << " " <<  size  << " " << 0 << " " <<  size << "\n"; //Ponto B
		file << " " << 0 << " " << 1 << " " << 0 << "\n"; //Normal B
		file << " " <<  size  << " " << 0 << " " << -size << "\n"; //Ponto C
		file << " " << 0 << " " << 1 << " " << 0 << "\n"; //Normal C

		file << " " <<  size  << " " << 0 << " " <<  size << "\n"; //Ponto B
		file << " " << 0 << " " << 1 << " " << 0 << "\n"; //Normal B
		file << " " << -size << " " << 0 << " " <<  -size << "\n"; //Ponto A
		file << " " << 0 << " " << 1 << " " << 0 << "\n"; //Normal A
		file << " " << -size << " " << 0 << " " <<   size << "\n"; //Ponto D
		file << " " << 0 << " " << 1 << " " << 0 << "\n"; //Normal D
	}
	else printf("File not opened\n");
	file.close();
}

/**
\brief Função que escreve os vértices de uma caixa num ficheiro
@param sizeX Comprimento da caixa
@param sizeY Altura da caixa
@param sizeZ Largura da caixa
@param divisions Número de divisões da caixa
@param name Ficheiro onde escrever os vértices
*/
void writeBoxFile(const char* sizeX, const char* sizeY, const char* sizeZ, const char* divisions, string name) {
	fstream file;
	file.open(name, ios::out);
	float x = atof(sizeX) / 2;
	float y = atof(sizeY) / 2;
	float z = atof(sizeZ) / 2;
	float d = atof(divisions);
	if (file.is_open()) {

		for (float i = 0; i < d; i++) {
			for (float j = 0; j < d; j++) {

				//Tras
				file << " " << -x + (j / d) * (x * 2) << " " << -y + ((i + 1) / d) * (y * 2) << " " << -z << "\n";
				file << " " << 0 << " " << 0 << " " << -1 << "\n"; //Normal Tras
				file << " " << -x + ((j + 1) / d) * (x * 2) << " " << -y + (i / d) * (y * 2) << " " << -z << "\n";
				file << " " << 0 << " " << 0 << " " << -1 << "\n"; //Normal Tras
				file << " " << -x + (j / d) * (x * 2) << " " << -y + (i / d) * (y * 2) << " " << -z << "\n";
				file << " " << 0 << " " << 0 << " " << -1 << "\n"; //Normal Tras

				file << " " << -x + (j / d) * (x * 2) << " " << -y + ((i + 1) / d) * (y * 2) << " " << -z << "\n";
				file << " " << 0 << " " << 0 << " " << -1 << "\n"; //Normal Tras
				file << " " << -x + ((j + 1) / d) * (x * 2) << " " << -y + ((i + 1) / d) * (y * 2) << " " << -z << "\n";
				file << " " << 0 << " " << 0 << " " << -1 << "\n"; //Normal Tras
				file << " " << -x + ((j + 1) / d) * (x * 2) << " " << -y + (i / d) * (y * 2) << " " << -z << "\n";
				file << " " << 0 << " " << 0 << " " << -1 << "\n"; //Normal Tras
				
				//Frente
				file << " " << -x + (j / d) * (x * 2) << " " << -y + (i / d) * (y * 2) << " " << z << "\n";
				file << " " << 0 << " " << 0 << " " << 1 << "\n"; //Normal Frente
				file << " " << -x + ((j + 1) / d) * (x * 2) << " " << -y + (i / d) * (y * 2) << " " << z << "\n";
				file << " " << 0 << " " << 0 << " " << 1 << "\n"; //Normal Frente
				file << " " << -x + ((j + 1) / d) * (x * 2) << " " << -y + ((i + 1) / d) * (y * 2) << " " << z << "\n";
				file << " " << 0 << " " << 0 << " " << 1 << "\n"; //Normal Frente

				file << " " << -x + (j / d) * (x * 2) << " " << -y + (i / d) * (y * 2) << " " << z << "\n";
				file << " " << 0 << " " << 0 << " " << 1 << "\n"; //Normal Frente
				file << " " << -x + ((j + 1) / d) * (x * 2) << " " << -y + ((i + 1) / d) * (y * 2) << " " << z << "\n";
				file << " " << 0 << " " << 0 << " " << 1 << "\n"; //Normal Frente
				file << " " << -x + (j / d) * (x * 2) << " " << -y + ((i + 1) / d) * (y * 2) << " " << z << "\n";
				file << " " << 0 << " " << 0 << " " << 1 << "\n"; //Normal Frente

				//Baixo
				file << " " << -x + (j / d) * (x * 2) << " " << -y << " " << -z + (i / d) * (z * 2) << "\n";
				file << " " << 0 << " " << -1 << " " << 0 << "\n"; //Normal Baixo
				file << " " << -x + ((j + 1) / d) * (x * 2) << " " << -y << " " << -z + (i / d) * (z * 2) << "\n";
				file << " " << 0 << " " << -1 << " " << 0 << "\n"; //Normal Baixo
				file << " " << -x + ((j + 1) / d) * (x * 2) << " " << -y << " " << -z + ((i + 1) / d) * (z * 2) << "\n";
				file << " " << 0 << " " << -1 << " " << 0 << "\n"; //Normal Baixo

				file << " " << -x + (j / d) * (x * 2) << " " << -y << " " << -z + (i / d) * (z * 2) << "\n";
				file << " " << 0 << " " << -1 << " " << 0 << "\n"; //Normal Baixo
				file << " " << -x + ((j + 1) / d) * (x * 2) << " " << -y << " " << -z + ((i + 1) / d) * (z * 2) << "\n";
				file << " " << 0 << " " << -1 << " " << 0 << "\n"; //Normal Baixo
				file << " " << -x + (j / d) * (x * 2) << " " << -y << " " << -z + ((i + 1) / d) * (z * 2) << "\n";
				file << " " << 0 << " " << -1 << " " << 0 << "\n"; //Normal Baixo
				//Cima
				file << " " << -x + (j / d) * (x * 2) << " " << y << " " << -z + (i / d) * (z * 2) << "\n";
				file << " " << 0 << " " << 1 << " " << 0 << "\n"; //Normal Cima
				file << " " << -x + ((j + 1) / d) * (x * 2) << " " << y << " " << -z + ((i + 1) / d) * (z * 2) << "\n";
				file << " " << 0 << " " << 1 << " " << 0 << "\n"; //Normal Cima
				file << " " << -x + ((j + 1) / d) * (x * 2) << " " << y << " " << -z + (i / d) * (z * 2) << "\n";
				file << " " << 0 << " " << 1 << " " << 0 << "\n"; //Normal Cima

				file << " " << -x + (j / d) * (x * 2) << " " << y << " " << -z + (i / d) * (z * 2) << "\n";
				file << " " << 0 << " " << 1 << " " << 0 << "\n"; //Normal Cima
				file << " " << -x + (j / d) * (x * 2) << " " << y << " " << -z + ((i + 1) / d) * (z * 2) << "\n";
				file << " " << 0 << " " << 1 << " " << 0 << "\n"; //Normal Cima
				file << " " << -x + ((j + 1) / d) * (x * 2) << " " << y << " " << -z + ((i + 1) / d) * (z * 2) << "\n";
				file << " " << 0 << " " << 1 << " " << 0 << "\n"; //Normal Cima
				//Esquerda
				file << " " << -x << " " << -y + (j / d) * (y * 2) << " " << -z + (i / d) * (z * 2) << "\n";
				file << " " << -1 << " " << 0 << " " << 0 << "\n"; //Normal Esquerda
				file << " " << -x << " " << -y + ((j + 1) / d) * (y * 2) << " " << -z + ((i + 1) / d) * (z * 2) << "\n";
				file << " " << -1 << " " << 0 << " " << 0 << "\n"; //Normal Esquerda
				file << " " << -x << " " << -y + ((j + 1) / d) * (y * 2) << " " << -z + (i / d) * (z * 2) << "\n";
				file << " " << -1 << " " << 0 << " " << 0 << "\n"; //Normal Esquerda

				file << " " << -x << " " << -y + (j / d) * (y * 2) << " " << -z + (i / d) * (z * 2) << "\n";
				file << " " << -1 << " " << 0 << " " << 0 << "\n"; //Normal Esquerda
				file << " " << -x << " " << -y + (j / d) * (y * 2) << " " << -z + ((i + 1) / d) * (z * 2) << "\n";
				file << " " << -1 << " " << 0 << " " << 0 << "\n"; //Normal Esquerda
				file << " " << -x << " " << -y + ((j + 1) / d) * (y * 2) << " " << -z + ((i + 1) / d) * (z * 2) << "\n";
				file << " " << -1 << " " << 0 << " " << 0 << "\n"; //Normal Esquerda

				//Direita
				file << " " << x << " " << -y + (j / d) * (y * 2) << " " << -z + (i / d) * (z * 2) << "\n";
				file << " " << 1 << " " << 0 << " " << 0 << "\n"; //Normal Direita
				file << " " << x << " " << -y + ((j + 1) / d) * (y * 2) << " " << -z + (i / d) * (z * 2) << "\n";
				file << " " << 1 << " " << 0 << " " << 0 << "\n"; //Normal Direita
				file << " " << x << " " << -y + (j / d) * (y * 2) << " " << -z + ((i + 1) / d) * (z * 2) << "\n";
				file << " " << 1 << " " << 0 << " " << 0 << "\n"; //Normal Direita

				file << " " << x << " " << -y + (j / d) * (y * 2) << " " << -z + ((i + 1) / d) * (z * 2) << "\n";
				file << " " << 1 << " " << 0 << " " << 0 << "\n"; //Normal Direita
				file << " " << x << " " << -y + ((j + 1) / d) * (y * 2) << " " << -z + (i / d) * (z * 2) << "\n";
				file << " " << 1 << " " << 0 << " " << 0 << "\n"; //Normal Direita
				file << " " << x << " " << -y + ((j + 1) / d) * (y * 2) << " " << -z + ((i + 1) / d) * (z * 2) << "\n";
				file << " " << 1 << " " << 0 << " " << 0 << "\n"; //Normal Direita
			}
		}

	}
	else printf("File not opened\n");
	file.close();
}

/**
\brief Função que escreve os vértices de um cone num ficheiro
@param r Raio do cone
@param h Altura do cone
@param sl Número de fatias do cone
@param st Número de camadas do cone
@param name Ficheiro onde escrever os vértices
*/
void writeConeFile(const char* r, const char* h, const char* sl, const char* st, string name) {
	fstream file;
	file.open(name, ios::out);
	if (file.is_open()) {
		float radius = atof(r);
		float height = atof(h);
		float slices = atoi(sl);
		float stacks = atoi(st);
		float slice = 2 * M_PI / slices; // Angulo de uma fatia
		float stackH = height / stacks; // Altura de uma camada
		float stackR = radius / stacks; // "Largura" de uma camada
		float z = atan(height/radius);//Declive do cone
		float ang = (pi / 2) - z;

		for (int i = 0; i < slices; i++) { // Itera pelas fatias
			float angle1 = i * slice;
			float angle2 = (i + 1) * slice;
			float p[3];

			//Cria a base
			file << " " << 0 << " " << 0 << " " << 0 << "\n";
			file << " " << 0 << " " << -1 << " " << 0 << "\n";//Normal base
			file << " " << radius * cos(angle1) << " " << 0 << " " << radius * sin(angle1) << "\n";
			file << " " << 0 << " " << -1 << " " << 0 << "\n";//Normal base
			file << " " << radius * cos(angle2) << " " << 0 << " " << radius * sin(angle2) << "\n";
			file << " " << 0 << " " << -1 << " " << 0 << "\n";//Normal base

			for (int j = 0; j < stacks - 1; j++) { //Itera pelas camadas ; Na ultima camada vai desenhar um por cima do outro
				float lowerH = j * stackH; // Altura na camada inferior
				float upperH = (j + 1) * stackH; // Altura na camada superior
				float lowerR = radius - stackR * j;// Raio para a camada inferior
				float upperR = radius - stackR * (j + 1);// Raio para a camada superior
				
				file << " " << upperR * cos(angle1) << " " << upperH << " " << upperR * sin(angle1) << "\n";
				p[0] = cos(angle1); p[1] = sin(ang); p[2] = sin(angle1); normalize(p);
				file << " " << p[0] << " " << p[1] << " " << p[2] << "\n"; //Normal
				
				file << " " << lowerR * cos(angle2) << " " << lowerH << " " << lowerR * sin(angle2) << "\n";
				p[0] = cos(angle2); p[1] = sin(ang); p[2] = sin(angle2); normalize(p);
				file << " " << p[0] << " " << p[1] << " " << p[2] << "\n"; //Normal
				
				file << " " << lowerR * cos(angle1) << " " << lowerH << " " << lowerR * sin(angle1) << "\n";
				p[0] = cos(angle1); p[1] = sin(ang); p[2] = sin(angle1); normalize(p);
				file << " " << p[0] << " " << p[1] << " " << p[2] << "\n"; //Normal

				file << " " << upperR * cos(angle1) << " " << upperH << " " << upperR * sin(angle1) << "\n";
				p[0] = cos(angle1); p[1] = sin(ang); p[2] = sin(angle1); normalize(p);
				file << " " << p[0] << " " << p[1] << " " << p[2] << "\n"; //Normal
				
				file << " " << upperR * cos(angle2) << " " << upperH << " " << upperR * sin(angle2) << "\n";
				p[0] = cos(angle2); p[1] = sin(ang); p[2] = sin(angle2); normalize(p);
				file << " " << p[0] << " " << p[1] << " " << p[2] << "\n"; //Normal
				
				file << " " << lowerR * cos(angle2) << " " << lowerH << " " << lowerR * sin(angle2) << "\n";
				p[0] = cos(angle2); p[1] = sin(ang); p[2] = sin(angle2); normalize(p);
				file << " " << p[0] << " " << p[1] << " " << p[2] << "\n"; //Normal

			}
			// Acabar com os triangulos do bico
			float lowerH = (stacks-1) * stackH; // Altura na camada inferior
			float upperH = stacks * stackH; // Altura na camada superior
			float lowerR = radius - stackR * (stacks - 1);// Raio para a camada inferior
			float upperR = radius - stackR * stacks;// Raio para a camada superior

			file << " " << upperR * cos(angle1) << " " << upperH << " " << upperR * sin(angle1) << "\n";
			p[0] = cos(angle1); p[1] = sin(ang); p[2] = sin(angle1); normalize(p);
			file << " " << p[0] << " " << p[1] << " " << p[2] << "\n"; //Normal
			
			file << " " << lowerR * cos(angle2) << " " << lowerH << " " << lowerR * sin(angle2) << "\n";
			p[0] = cos(angle2); p[1] = sin(ang); p[2] = sin(angle2); normalize(p);
			file << " " << p[0] << " " << p[1] << " " << p[2] << "\n"; //Normal
			
			file << " " << lowerR * cos(angle1) << " " << lowerH << " " << lowerR * sin(angle1) << "\n";
			p[0] = cos(angle1); p[1] = sin(ang); p[2] = sin(angle1); normalize(p);
			file << " " << p[0] << " " << p[1] << " " << p[2] << "\n"; //Normal
		}
	}
	else printf("File not opened\n");
	file.close();
}

/** Recebe o nome da forma a gerar, os seus parâmetros e o ficheiro onde escrever os vértices da forma */
int main(int argc, const char* argv[]) {
	string forma = string(argv[1]);
	string fileName = string(argv[argc - 1]);
	if (!forma.compare("sphere") && argc == 6) { writeSphereFile(argv[2], argv[3], argv[4], fileName); }
	else if (!forma.compare("plane") && argc == 4) { writePlaneFile(argv[2], fileName); }
	else if (!forma.compare("box") && argc == 7) { writeBoxFile(argv[2], argv[3], argv[4], argv[5], fileName); }
	else if (!forma.compare("cone") && argc == 7) { writeConeFile(argv[2], argv[3], argv[4], argv[5], fileName); }
	else if (argc == 4) { writePatchFile(argv[1], argv[2],fileName); }
	return 1;
}
