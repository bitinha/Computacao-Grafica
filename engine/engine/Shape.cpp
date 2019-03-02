#include "Shape.h"
#include "Vertice.h"
#include <vector>
#include "glut.h"


Shape::Shape()
{
	std::vector<Vertice> vertices;
}


Shape::~Shape()
{
}

void Shape::addVertice(Vertice v)
{
	vertices.push_back(v);
}

void Shape::setVertices(std::vector<Vertice> v)
{
	vertices = v;
}

void Shape::draw()
{
	std::vector<Vertice> ::iterator it;
	Vertice ponto;
	glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_TRIANGLES);
	for (it = vertices.begin(); it != vertices.end(); it++) {
		ponto = *it;
		glVertex3f(ponto.getX(), ponto.getY(), ponto.getZ());
	}
	glEnd();
}
