#include <vector>
#include "Figura.h"
#include "tinyxml2.h"
#include "Cena.h"

using namespace tinyxml2;

vector<Figura> xmlParser(const char* filename);
vector<Figura> trataGrupo(XMLNode * node, vector<Figura> figuras, vector<Transformacao> atual);
vector<Figura> models(vector<Figura> figuras, XMLNode * element, vector<Transformacao> atual);
float str2Float(const char * str);
vector<Cena> getCenas(vector<Figura> figuras);