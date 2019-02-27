#include <iostream>
#include <vector>
#include "tinyxml2.h";
#include <string>;
#include <list>;
#include "Shape.h"
#include "Sphere.h"

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

using namespace tinyxml2;
using namespace std;

Sphere criaEsfera(FILE *file) {
	float radius = 0;
	int stacks = 0;
	int slices = 0;
	fscanf_s(file, "Radius: %f\n", radius);
	fscanf_s(file, "Slices: %i\n", slices);
	fscanf_s(file, "Stacks: %i\n", stacks);

	return Sphere(radius, slices, stacks);
}

Shape novaForma(char forma[], FILE* file) {
	string shape = string(forma);
	if (!shape.compare("sphere")) { return (criaEsfera(file)); }
	/*else if (!shape.compare("plane")) { return (criaPlano(file));}
	else if (!shape.compare("box")) { return (criaBox(file));}
	else if (!shape.compare("cone")) { return (criaCone(file));}*/
}

list<Shape> interpretador(list<string> files) {
	for (std::list<string>::iterator it = files.begin(); it != files.end(); ++it)
		std::cout << ' ' << *it;
	list<Shape> sh;
	list<Shape> ::iterator iter;
	errno_t erro;
	for (list<string>::iterator it = files.begin(); it != files.end(); it++) {
		FILE *pfile;
		if (erro = fopen_s(&pfile, (*it).c_str(), "r") != 0) {
			char forma[10];
			fscanf_s(pfile, "Forma: %s\n", forma, sizeof(forma));
			std::cout << ' ' << forma;
			for (;;);
			sh.insert(iter, novaForma(forma, pfile));
			fclose(pfile);
		}
	}
	return sh;
}

int main() {

	list<string> files;
	list<string> ::iterator it;
	int i = 0;

	it = files.begin();

	/*Ler um ficheiro XML*/
	list<Shape> formas;
	XMLDocument xmlDoc;
	const char * filename = "../teste.xml";
	XMLError eResult = xmlDoc.LoadFile((char*)filename);

	XMLNode * pRoot = xmlDoc.FirstChild();
	if (pRoot == nullptr) return XML_ERROR_FILE_READ_ERROR;

	XMLElement * pElement = pRoot->FirstChildElement("model");
	if (pElement == nullptr) return XML_ERROR_PARSING_ELEMENT;

	const char * szAttributeText = nullptr;
	XMLElement * pListElement = pRoot->FirstChildElement("model");

	while (pListElement != nullptr) {
		const char* iOutListValue;
		iOutListValue = pListElement->Attribute("file");
		files.insert(it, iOutListValue);
		pListElement = pListElement->NextSiblingElement("model");
	}

	for (std::list<string>::iterator it = files.begin(); it != files.end(); ++it)
		std::cout << ' ' << *it;

	formas = interpretador(files);
	return 1;
}