#pragma once
#include <vector>
#include "Vertice.h"
class Shape
{
public:
	std:: vector <Vertice> vertices;
	Shape();
	~Shape();
	void addVertice(Vertice v);
	void setVertices(std::vector<Vertice> v);
	void draw();
};

