#include "Grupo.h"
#include "Luz.h"
#include <vector>

using namespace std;

class Cena
{
public: 
	vector<Grupo*> grupos;
	Luz* luz;
	
	Cena();
	Cena(vector<Grupo*> grupo, Luz* l);
	~Cena();
	Luz* getLuz();
	void setLuz(Luz* l);
	vector<Grupo*> getGrupos();
	void setGrupos(vector<Grupo*> g);
};