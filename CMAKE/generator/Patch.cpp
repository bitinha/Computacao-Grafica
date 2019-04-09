#include "Patch.h"

Patch::Patch()
{
}

Patch::~Patch()
{
}

vector<int> Patch::getIndices() {
	return this->indices;
}

vector<Ponto*> Patch::getPontos() {
	return this->pontos;
}

void Patch::setIndices(vector<int> indices) {
	this->indices = indices;
}

void Patch::addIndice(int indice) {
	this->indices.push_back(indice);
}
/*
Ponto getPontoByIndex(vector<Ponto> cp,int index){
	return cp.at(this->indices(index));
}
*/

Ponto* bezier(float t, Ponto p0, Ponto p1, Ponto p2, Ponto p3){
	float T[4] = {pow(t,3),pow(t,2),t,1};
	float M[4][4] = { {-1, 3,-3, 1},
					  { 3,-6, 3, 0},
					  {-3, 3, 0, 0},
					  { 1, 0, 0, 0} };
	
	float A[4][3];
	//M*P
	for (int i = 0; i < 4; i++) {
		A[i][0] = p0.getX() * M[i][0] + p1.getX() * M[i][1] + p2.getX() * M[i][2] + p3.getX() * M[i][3];
		A[i][1] = p0.getY() * M[i][0] + p1.getY() * M[i][1] + p2.getY() * M[i][2] + p3.getY() * M[i][3];
		A[i][2] = p0.getZ() * M[i][0] + p1.getZ() * M[i][1] + p2.getZ() * M[i][2] + p3.getZ() * M[i][3];
	}
	
	//T*A
	float x = T[0]*A[0][0] + T[1]*A[1][0] + T[2]*A[2][0] + T[3]*A[3][0];
	float y = T[0]*A[0][1] + T[1]*A[1][1] + T[2]*A[2][1] + T[3]*A[3][1];
	float z = T[0]*A[0][2] + T[1]*A[1][2] + T[2]*A[2][2] + T[3]*A[3][2];
	
	return new Ponto(x,y,z);
}

void Patch::geraPontos(vector<Ponto*> cp, int tesselation){
	
	//float step = 1/(float)tesselation;
	vector<Ponto*> ps; 
	
	for (int i = 0; i <= tesselation; i++) {
		float u = i/(float)tesselation;
		Ponto* pu0 = bezier(u,*cp.at(this->indices.at(0)),*cp.at(this->indices.at(1)),*cp.at(this->indices.at(2)),*cp.at(this->indices.at(3)));
		Ponto* pu1 = bezier(u,*cp.at(this->indices.at(4)),*cp.at(this->indices.at(5)),*cp.at(this->indices.at(6)),*cp.at(this->indices.at(7)));
		Ponto* pu2 = bezier(u,*cp.at(this->indices.at(8)),*cp.at(this->indices.at(9)),*cp.at(this->indices.at(10)),*cp.at(this->indices.at(11)));
		Ponto* pu3 = bezier(u,*cp.at(this->indices.at(12)),*cp.at(this->indices.at(13)),*cp.at(this->indices.at(14)),*cp.at(this->indices.at(15)));

		for(int j = 0; j<=tesselation; j++){
			float v = j/(float)tesselation;
			Ponto* pv = bezier(v,*pu0,*pu1,*pu2,*pu3);
			ps.push_back(pv);
		}
	}
	for(int i = 0; i < tesselation; i++){
		for(int j = 0;j < tesselation; j++){
			this->pontos.push_back(ps.at(i * tesselation + j));
			this->pontos.push_back(ps.at(i * tesselation + j + 1));
			this->pontos.push_back(ps.at(i * tesselation + j + tesselation + 1));
			
			this->pontos.push_back(ps.at(i * tesselation + j));
			this->pontos.push_back(ps.at(i * tesselation + j + tesselation + 1));
			this->pontos.push_back(ps.at(i * tesselation + j + tesselation));
		}	
	}
	
}