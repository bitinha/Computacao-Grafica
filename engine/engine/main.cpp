#include <iostream>
#include <vector>
#include "tinyxml2.h";
#include <string>;
#include <list>;

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

using namespace tinyxml2;
using namespace std;

int main() {

	list<string> files;
	list<string> ::iterator it;
	int i = 0;

	it = files.begin();

	/*Ler um ficheiro XML*/
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
}
