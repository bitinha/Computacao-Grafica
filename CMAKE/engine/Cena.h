#include "Grupo.h"
#include "Luz.h"
#include <vector>

using namespace std;

class Cena
{
public: 
	vector<Grupo*> grupos;
	vector<Luz*> luz;
	
	Cena();
	Cena(vector<Grupo*> grupo, vector<Luz*> l);
	~Cena();
	vector<Luz*> getLuz();
	void setLuz(vector<Luz*> l);
	vector<Grupo*> getGrupos();
	void setGrupos(vector<Grupo*> g);
	void ilumina();
};