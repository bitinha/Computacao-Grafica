#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include "tinyxml2.h"
#include "Transformacao.h"
#include "Figura.h"
#include "Translacao.h"
#include "Rotacao.h"
#include "Scale.h"
#include "Cena.h"

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

using namespace std;
using namespace tinyxml2;

float str2Float(const char * str) {

	if (str == nullptr) {
		return 0;
	}
	return atof(str);
}

/**
\brief Função que devolve uma Shape(vetor com vértices) a partir de uma lista de ficheiros com vértices
@param 
@return
*/
vector<float> interpretador(Figura f) {

	vector<float> point;
	errno_t erro;
	float px = 0, py = 0, pz = 0;
	char* file = _strdup(f.getFile());
	int ch, ok;
	FILE *pfile;
	erro = fopen_s(&pfile, file, "r");
	if (erro == 0) {
		while (EOF != (ch = getc(pfile))) {
			ok = fscanf_s(pfile, "%f ", &px, sizeof(px));
			fscanf_s(pfile, "%f ", &py, sizeof(py));
			fscanf_s(pfile, "%f", &pz, sizeof(pz));
			if (ok >= 0) {
				point.push_back(px);
				point.push_back(py);
				point.push_back(pz);
			}
		}
		fclose(pfile);
	}

	return point;
}

vector<Cena> getCenas(vector<Figura> figuras) {
	vector<Cena> cenas;
	for (vector<Figura>::iterator it = figuras.begin(); it != figuras.end(); it++) {
		vector<float> pontos = interpretador((*it));
		Cena c = Cena((*it).getTransformacoes(), pontos);
		cenas.push_back(c);
	}
	return cenas;
}
vector<Figura> models(vector<Figura> figuras, XMLNode * element, vector<Transformacao> atual) {

	while (element != nullptr) {
		XMLElement * model = element->ToElement();
		const char* iOutListValue;
		iOutListValue = model->Attribute("file");
		Figura f = Figura(atual, (char*)iOutListValue);
		figuras.push_back(f);
		element = element->NextSibling();
	}
	return figuras;
}

vector<Figura> trataGrupo(XMLNode * node, vector<Figura> figuras, vector<Transformacao> atual) {
	XMLNode * element = node;
	XMLElement * transformacao;
	while (node != nullptr) {
		if (!strcmp(node->Value(), "group")) {
			element = node->FirstChild();
			figuras = trataGrupo(element, figuras, atual);
			node = node->NextSibling();
		}
		else if (!strcmp(node->Value(), "models")) {
			element = node->FirstChild();
			figuras = models(figuras, element, atual);
			node = node->NextSibling();
		}
		else if (!strcmp(node->Value(), "translation")) {
			transformacao = node->ToElement();
			float dx = str2Float(transformacao->Attribute("x"));
			float dy = str2Float(transformacao->Attribute("y"));
			float dz = str2Float(transformacao->Attribute("z"));
			Translacao t = Translacao(dx, dy, dz);
			atual.push_back(t);
			node = node->NextSibling();
		}
		else if (!strcmp(node->Value(), "scale")) {
			transformacao = node->ToElement();
			float dx = str2Float(transformacao->Attribute("x"));
			float dy = str2Float(transformacao->Attribute("y"));
			float dz = str2Float(transformacao->Attribute("z"));
			Scale t = Scale(dx, dy, dz);
			atual.push_back(t);
			node = node->NextSibling();
		}
		else if (!strcmp(node->Value(), "rotate")) {
			transformacao = node->ToElement();
			float angle = str2Float(transformacao->Attribute("angle"));
			float dx = str2Float(transformacao->Attribute("x"));
			float dy = str2Float(transformacao->Attribute("y"));
			float dz = str2Float(transformacao->Attribute("z"));
			Rotacao t = Rotacao(angle, dx, dy, dz);
			atual.push_back(t);
			node = node->NextSibling();
		}
	}

	return figuras;
}
/**
\brief Função que escreve os vértices de uma caixa num ficheiro
@param filename Ficheiro xml a ler
@return Ficheiros que se devem ler
*/
vector<Figura> xmlParser(const char* filename) {

	list<string> files;
	list<string> ::iterator it;
	/*Ler um ficheiro XML*/
	XMLDocument xmlDoc;
	XMLError eResult = xmlDoc.LoadFile(filename);

	if (eResult) {
		printf("Não foi possível carregar o ficheiro xml");
		exit(1);
	}

	XMLNode * pRoot = xmlDoc.FirstChild();
	XMLNode * element;
	if (pRoot == nullptr) {
		printf("Erro ao ler o ficheiro xml");
		exit(XML_ERROR_FILE_READ_ERROR);
	}

	vector<Figura> figuras;
	vector<Transformacao> atual;

	pRoot = pRoot->FirstChild();
	while (pRoot != nullptr) {
		element = pRoot->FirstChild();
		figuras = trataGrupo(element, figuras, atual);
		pRoot = pRoot->NextSibling();
	}
	return figuras;
}