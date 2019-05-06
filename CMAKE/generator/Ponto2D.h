#pragma once

using namespace std;
class Ponto2D
{
public: float x;
		float y;

		Ponto2D();
		Ponto2D(float x, float y);
		~Ponto2D();

		float getX();
		float getY();
};