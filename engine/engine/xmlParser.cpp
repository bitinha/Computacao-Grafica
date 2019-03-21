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
#include "Grupo.h"

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
vector<float> interpretador(const char * file) {

	vector<float> point;
	errno_t erro;
	float px = 0, py = 0, pz = 0;
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

Grupo* models(Grupo *group, XMLNode * element) {

	while (element != nullptr) {
		XMLElement * model = element->ToElement();
		const char* iOutListValue;
		iOutListValue = model->Attribute("file");
		vector<float> pontos = interpretador(iOutListValue);
		group->addPontos(pontos);
		element = element->NextSibling();
	}
	return group;
}

Grupo* trataGrupo(XMLNode * node) {
	XMLNode * element = node;
	XMLElement * transformacao;
	vector<Transformacao*> atual;
	Grupo *gr = new Grupo;
	while (node != nullptr) {
		if (!strcmp(node->Value(), "group")) {
			element = node->FirstChild();
			Grupo *g = trataGrupo(element);
			gr->addGrupo(g);
			node = node->NextSibling();
		}
		else if (!strcmp(node->Value(), "models")) {
			element = node->FirstChild();
			vector<Grupo> grupos;
			vector<float> pontos;
			gr = models(gr, element);
			node = node->NextSibling();
		}
		else if (!strcmp(node->Value(), "translate")) {
			transformacao = node->ToElement();
			float dx = str2Float(transformacao->Attribute("X"));
			float dy = str2Float(transformacao->Attribute("Y"));
			float dz = str2Float(transformacao->Attribute("Z"));
			Translacao *t = new Translacao(dx, dy, dz);
			atual.push_back(t);
			node = node->NextSibling();
		}
		else if (!strcmp(node->Value(), "scale")) {
			transformacao = node->ToElement();
			float dx = str2Float(transformacao->Attribute("X"));
			float dy = str2Float(transformacao->Attribute("Y"));
			float dz = str2Float(transformacao->Attribute("Z"));
			Scale *t = new Scale(dx, dy, dz);
			atual.push_back(t);
			node = node->NextSibling();
		}
		else if (!strcmp(node->Value(), "rotate")) {
			transformacao = node->ToElement();
			float angle = str2Float(transformacao->Attribute("angle"));
			float dx = str2Float(transformacao->Attribute("X"));
			float dy = str2Float(transformacao->Attribute("Y"));
			float dz = str2Float(transformacao->Attribute("Z"));
			Rotacao *t = new Rotacao(angle, dx, dy, dz);
			atual.push_back(t);
			node = node->NextSibling();
		}
	}
	gr->setTransformacoes(atual);
	return gr;
}


/**
\brief Função que escreve os vértices de uma caixa num ficheiro
@param filename Ficheiro xml a ler
@return Ficheiros que se devem ler
*/
vector<Grupo*> xmlParser(const char* filename) {

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

	vector<Grupo*> grupos;

	pRoot = pRoot->FirstChild();
	while (pRoot != nullptr) {
		element = pRoot->FirstChild();
		Grupo *group = trataGrupo(element);
		grupos.push_back(group);
		pRoot = pRoot->NextSibling();
	}
	return grupos;
}
