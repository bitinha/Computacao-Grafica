#include <iostream>
#include <vector>
#include "tinyxml2.h";
#include <string.h>;
#include <list>;
#include "Shape.h"
#include "Sphere.h"

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

using namespace tinyxml2;
using namespace std;
/*
list<Shape> interpretador(list<string> files) {

	for (list<string>::iterator it = files.begin(); it != files.end(); it++) {
		FILE *pfile;
		pfile = fopen((*it).c_str(),"r");
		char forma[10];
		fscanf(pfile,"Forma: %s\n",forma);

	}
}

Sphere criaEsfera(FILE *file) {
	float radius = 0;
	int stacks = 0;
	int slices = 0;
	fscanf(file, "Radius: %f\n",  radius);
	fscanf(file, "Slices: %i\n", slices);
	fscanf(file, "Stacks: %i\n", stacks);
	
	return Sphere(radius, slices, stacks);
}

Shape novaForma(char forma[], FILE* file) {
	string shape = string(forma);
	if (!shape.compare("sphere")) { return (criaEsfera(file));}
	else if (!shape.compare("plane")) { return (criaPlano(file));}
	else if (!shape.compare("box")) { return (criaBox(file));}
	else if (!shape.compare("cone")) { return (criaCone(file));}
}
*/