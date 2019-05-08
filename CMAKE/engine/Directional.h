#include "Luz.h"
#include <GL/glut.h>

class Directional : public Luz
{
public:
	Directional();
	Directional(float p[3], float diff[3], float s[3], float a[3]);
	~Directional();
	void ilumina(int i);
};