
#include <vector>
using namespace std;
class Patch
{
public: vector<int> indices;
		vector<Ponto> pontos;

		Patch();
		~Patch();
		vector<int> getIndices();
		void setIndices(vector<int> indices);
		void addIndice(int indice);
};