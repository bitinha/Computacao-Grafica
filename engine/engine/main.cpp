#include <iostream>
#include <vector>
#include "tinyxml2.h";
#include <string>;
#include <list>;
#include "Shape.h"
#include "Sphere.h"
#include "Cone.h"
#include "Box.h"
#include "Plane.h"

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

using namespace tinyxml2;
using namespace std;

Sphere criaEsfera(FILE *file) {
	float radius = 0;
	int stacks = 0;
	int slices = 0;
	fscanf_s(file, "Radius: %f\n", &radius);
	fscanf_s(file, "Slices: %i\n", &slices);
	fscanf_s(file, "Stacks: %i", &stacks);

	return Sphere(radius, slices, stacks);
}

Cone criaCone(FILE *file) {
	float radius = 0;
	float height = 0;
	int stacks = 0;
	int slices = 0;
	fscanf_s(file, "Radius: %f\n", &radius);
	fscanf_s(file, "Height: %f\n", &height);
	fscanf_s(file, "Slices: %i\n", &slices);
	fscanf_s(file, "Stacks: %i", &stacks);

	return Cone(radius, height, slices, stacks);
}

Box criaBox(FILE *file) {
	double x = 0;
	double y = 0;
	double z = 0;
	int divisions = 0;
	fscanf_s(file, "X: %d\n", &x);
	fscanf_s(file, "Y: %d\n", &y);
	fscanf_s(file, "Z: %d\n", &z);
	fscanf_s(file, "Divisions: %i", &divisions);

	return Box(x, y, z, divisions);
}

Plane criaPlano(FILE *file) {
	double x = 0;
	double z = 0;
	fscanf_s(file, "X: %d\n", &x);
	fscanf_s(file, "Z: %d\n", &z);

	return Plane(x, z);
}

Shape novaForma(char forma[], FILE* file) {
	string shape = string(forma);
	if (!shape.compare("sphere")) { return (criaEsfera(file)); }
	else if (!shape.compare("plane")) { return (criaPlano(file));}
	else if (!shape.compare("box")) { return (criaBox(file));}
	else if (!shape.compare("cone")) { return (criaCone(file));}
}

list<Shape> interpretador(list<string> files) {
	for (std::list<string>::iterator it = files.begin(); it != files.end(); ++it)
		std::cout << ' ' << *it;
	std::list<Shape> sh;
	list<Shape> ::iterator iter = sh.begin();
	errno_t erro;
	for (list<string>::iterator it = files.begin(); it != files.end(); it++) {
		FILE *pfile;
		erro = fopen_s(&pfile, (*it).c_str(), "r");
		std::cout << ' ' << erro;
		if ( erro == 0) {
			char forma[10];
			fscanf_s(pfile, "Forma: %s\n", forma, sizeof(forma));
			std::cout << ' ' << forma;
			Shape s = novaForma(forma, pfile);
			sh.insert(iter, s);
			fclose(pfile);
		}
	}
	return sh;
}

list<string> extraiFicheiros(const char* filename) {


	list<string> files;
	list<string> ::iterator it;
	/*Ler um ficheiro XML*/
	XMLDocument xmlDoc;
	XMLError eResult = xmlDoc.LoadFile((char*)filename);

	if (eResult) {
		printf("Não foi possível carregar o ficheiro xml");
		exit(1);
	}



	XMLNode * pRoot = xmlDoc.FirstChild();
	if (pRoot == nullptr) {
		printf("Erro ao ler o ficheiro xml");
		exit(XML_ERROR_FILE_READ_ERROR);
	}

	XMLElement * pElement = pRoot->FirstChildElement("model");
	if (pElement == nullptr) {
		printf("Erro ao ler o ficheiro xml");
		exit(XML_ERROR_PARSING_ELEMENT);
	}

	const char * szAttributeText = nullptr;
	XMLElement * pListElement = pRoot->FirstChildElement("model");
	it = files.begin();
	while (pListElement != nullptr) {
		const char* iOutListValue;
		iOutListValue = pListElement->Attribute("file");
		files.insert(it, iOutListValue);
		pListElement = pListElement->NextSiblingElement("model");
	}

	return files;

}

int main(int argc, const char* argv[]) {

	if (argc < 2) {

		printf("Indique um ficheiro a partir do qual se deva gerar");
		return 1;
	}

	const char * filename = argv[1];

	list<Shape> formas;
	list<string> files = extraiFicheiros(filename);

	list<string> ::iterator it;
	it = files.begin();

	for (std::list<string>::iterator it = files.begin(); it != files.end(); ++it)
		std::cout << ' ' << *it << '\n';

	formas = interpretador(files);
	return 0;
}