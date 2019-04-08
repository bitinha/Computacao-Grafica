#include "Patch.h"
#include <vector>
using namespace std;
class Patches
{
public: vector<float> pontos;
		int nPatches;
		int nCP;
		vector<Patch> patches;
		int tesselation;
		
		Patches();
		~Patches();
		vector<float> generatePoints();
		void write(FILE *filename);
};