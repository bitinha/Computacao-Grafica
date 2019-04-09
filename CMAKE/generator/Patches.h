#pragma once
#include "Ponto.h"
#include "Patch.h"
#include <vector>
using namespace std;
class Patches
{
public: vector<Ponto*> pontos;
		int nPatches;
		int nCP;
		vector<Patch*> patches;
		int tesselation;
		
		Patches();
		~Patches();
		void setNPatches(int nPatches);
		void setNCP(int nCP);
		void setTesselation(int tesselation);

		vector<Ponto*> generatePoints();
		void addPatch(Patch *p);
		void addPonto(Ponto *ponto);
};