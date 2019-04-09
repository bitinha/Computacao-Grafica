#include "Patch.h"
#include <vector>
using namespace std;
class Patches
{
public: vector<Ponto> pontos;
		int nPatches;
		int nCP;
		vector<Patch> patches;
		int tesselation;
		
		Patches();
		~Patches();
		void setNPatches(int nPatches);
		void setNCP(int nCP);

		vector<float> generatePoints();
		void write(FILE *filename);
		void addPatches(Patch p);
		void addPontos(Ponto ponto);
};