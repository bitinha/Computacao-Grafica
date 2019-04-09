#pragma once

using namespace std;
class Ponto
{
public: float x;
		float y;
		float z;

		Ponto();
		Ponto(float x, float y, float z);
		~Ponto();
		
		float getX();
		float getY();
		float getZ();
		
};