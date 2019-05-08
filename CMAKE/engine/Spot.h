#include "Luz.h"
#include <GL/glut.h>

class Spot: public Luz
{
public: GLfloat angle;
		GLfloat exponent;
		float atenuacao;
		float spotDirection[3];
		Spot();
		Spot(float p[3], float diff[3], float s[3], float a[3], float dir[3], GLfloat angle, GLfloat exponent, float atenuacao);
		~Spot();
		void ilumina(int i);
};
