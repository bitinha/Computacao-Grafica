#include <iostream>
#include <list>
#include "xmlParser.h"
#include "Translacao.h"
#include "Rotacao.h"
#include "Scale.h"
#include "FiguraDifusa.h"
#include "PointLight.h"
#include "Directional.h"
#include "Spot.h"

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

using namespace std;
using namespace tinyxml2;


float str2Num(const char * str) {

	if (str == nullptr) {
		return 1;
	}
	return atof(str);
}


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

Figura interpretador(const char * file){
	Figura fig; 
	int x = 0;
	vector<float> normais;
	vector<float> point;
	//vector<float> textura;
	errno_t erro;
	float px = 0, py = 0, pz = 0;
	int ch, ok;
	FILE *pfile;
	erro = fopen_s(&pfile, file, "r");
	if (erro == 0) {
		while (EOF != (ch = getc(pfile))) {
			//if (x % 2 == 0){
					ok = fscanf_s(pfile, "%f ", &px, sizeof(px));
					fscanf_s(pfile, "%f ", &py, sizeof(py));
					fscanf_s(pfile, "%f", &pz, sizeof(pz));
					point.push_back(px);
					point.push_back(py);
					point.push_back(pz);
				//}
			/*
			else if (x % 2 == 1) {
				ok = fscanf_s(pfile, "%f ", &px, sizeof(px));
				fscanf_s(pfile, "%f ", &py, sizeof(py));
				fscanf_s(pfile, "%f", &pz, sizeof(pz));
				normais.push_back(px);
				normais.push_back(py);
				normais.push_back(pz);
			}
			else{
				ok = fscanf_s(pfile, "%f ", &px, sizeof(px));
				fscanf_s(pfile, "%f ", &py, sizeof(py));
				textura.push_back(px);
				textura.push_back(py);
			}*/
			x++;
		}
	}
	fclose(pfile);
	fig.setPontos(point);
	//fig.setNormais(normais);
	//fig.setTextura(textura);
	return fig;
}

vector<Ponto> getControlPoints(XMLNode * element) {
	
	vector<Ponto> pontos;
	while (element != nullptr) {
		XMLElement * point = element->ToElement();
		float dx = str2Float(point->Attribute("X"));
		float dy = str2Float(point->Attribute("Y"));
		float dz = str2Float(point->Attribute("Z"));
		Ponto p = Ponto(dx, dy, dz);
		pontos.push_back(p);
		element = element->NextSibling();
	}
	return pontos;
}

Grupo* models(Grupo *group, XMLNode * element) {
	while (element != nullptr) {
		XMLElement * model = element->ToElement();
		const char* iOutListValue, *diffR, *diffG, *diffB, *colorR, *colorG, *colorB, *emissiveR, *emissiveG, *emissiveB, *ambientR, *ambientG, *ambientB, *specularR, *specularG, *specularB;
		float r, g, b, cR, cG, cB, dR, dG, dB, eR, eG, eB, aR, aG, aB, sR, sG, sB;
		//if (model->Attribute("texture") == nullptr) {		
		colorR = model->Attribute("colorR");
		colorG = model->Attribute("colorG");
		colorB = model->Attribute("colorB");
		diffR = model->Attribute("diffR");
		diffG = model->Attribute("diffG");
		diffB = model->Attribute("diffB");
		emissiveR = model->Attribute("emissiveR");
		emissiveG = model->Attribute("emissiveG");
		emissiveB = model->Attribute("emissiveB");
		specularR = model->Attribute("specularR");
		specularG = model->Attribute("specularG");
		specularB = model->Attribute("specularB");
		ambientR = model->Attribute("ambientR");
		ambientG = model->Attribute("ambientG");
		ambientB = model->Attribute("ambientB");
		
		r = str2Num(colorR);
		g = str2Num(colorG);
		b = str2Num(colorB);
		dR = str2Num(diffR);
		dG = str2Num(diffG);
		dB = str2Num(diffB);
		eR = str2Num(emissiveR);
		eG = str2Num(emissiveG);
		eB = str2Num(emissiveB);
		aR = str2Num(ambientR);
		aG = str2Num(ambientG);
		aB = str2Num(ambientB);
		sR = str2Num(specularR);
		sG = str2Num(specularG);
		sB = str2Num(specularB);

		float diffuse[3] = {dR, dG, dB};
		float emissive[3] = {eR, eG, eB };
		float specular[3] = {sR, sG, sB };
		float ambient[3] = {aR, aG, aB };

		iOutListValue = model->Attribute("file");
		Figura fig = interpretador(iOutListValue);
		FiguraDifusa* dif = new FiguraDifusa(r, g, b, diffuse, specular, emissive, ambient, fig.getPontos()/*,fig.getNormais(), fig.getTextura()*/);
		group->addFigura(dif);
		element = element->NextSibling();
		//}
		/*
		else fazer a textura
		*/
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
			if (transformacao->Attribute("time") != nullptr) {
				float time = str2Float(transformacao->Attribute("time"));
				element = node->FirstChild();
				vector<Ponto> controlPoints = getControlPoints(element);
				TranslacaoDinamica td = TranslacaoDinamica(time, controlPoints);
				(*gr).setTransDinamica(td);
			}
			else {
				float dx = str2Float(transformacao->Attribute("X"));
				float dy = str2Float(transformacao->Attribute("Y"));
				float dz = str2Float(transformacao->Attribute("Z"));
				Translacao *t = new Translacao(dx, dy, dz);
				atual.push_back(t);
			}
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
			float dx = str2Float(transformacao->Attribute("axisX"));
			float dy = str2Float(transformacao->Attribute("axisY"));
			float dz = str2Float(transformacao->Attribute("axisZ"));
			if (transformacao->Attribute("time") != nullptr) {
				float time = str2Float(transformacao->Attribute("time"));
				RotacaoDinamica rd = RotacaoDinamica(time, dx, dy, dz);
				(*gr).setRotacaoDinamica(rd);
			}
			else {
				float angle = str2Float(transformacao->Attribute("angle"));
				Rotacao *t = new Rotacao(angle, dx, dy, dz);
				atual.push_back(t);
			}
			node = node->NextSibling();
		}
		else {
			node = node->NextSibling();
		}
	}
	gr->setTransformacoes(atual);
	return gr;
}

Luz* trataLuz(XMLNode * node) {
	XMLNode * element = node;
	XMLElement * transformacao;
	Luz* l = nullptr;

	while (node != nullptr) {
		if (!strcmp(node->Value(), "light")) {
			transformacao = node->ToElement();
			if (!strcmp(transformacao->Attribute("type"), "POINT")) {
				float dx = str2Float(transformacao->Attribute("posX"));
				float dy = str2Float(transformacao->Attribute("posY"));
				float dz = str2Float(transformacao->Attribute("posZ"));
				PointLight* p = new PointLight(dx, dy, dz);
				l = p;
			}
			else if (!strcmp(transformacao->Attribute("type"), "DIRECTIONAL")) {
				float dx = str2Float(transformacao->Attribute("dirX"));
				float dy = str2Float(transformacao->Attribute("dirY"));
				float dz = str2Float(transformacao->Attribute("dirZ"));
				Directional* p = new Directional(dx, dy, dz);
				l = p;
			}
			else if (!strcmp(transformacao->Attribute("type"), "SPOT")) {
				float dx = str2Float(transformacao->Attribute("dirX"));
				float dy = str2Float(transformacao->Attribute("dirY"));
				float dz = str2Float(transformacao->Attribute("dirZ"));
				float angle = str2Float(transformacao->Attribute("angle"));
				Spot* p = new Spot(dx, dy, dz, angle);
				l = p;
			}
			else;
			node = node->NextSibling();
		}
		else {
			node = node->NextSibling();
		}
	}

	return l;
}


/**
\brief Função que escreve os vértices de uma caixa num ficheiro
@param filename Ficheiro xml a ler
@return Ficheiros que se devem ler
*/
Cena xmlParser(const char* filename) {
	Cena c;
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
	Luz* l = nullptr;

	pRoot = pRoot->FirstChild();
	
	if (strcmp(pRoot->Value(), "lights") == 0) {
		element = pRoot->FirstChild();
		l = trataLuz(element);
		pRoot = pRoot->NextSibling();
	}
	
	while (pRoot != nullptr) {
		element = pRoot->FirstChild();
		Grupo *group = trataGrupo(element);
		grupos.push_back(group);
		pRoot = pRoot->NextSibling();
	}

	c = Cena(grupos, l);
	
	return c;
}
