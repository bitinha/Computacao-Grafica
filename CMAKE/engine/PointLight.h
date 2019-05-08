#include "Luz.h"
#include <GL/glut.h>

class PointLight : public Luz
{
public:
		float atenuacao;
		PointLight();
		PointLight(float p[3], float diff[3], float s[3], float a[3], float atenuacao);
		~PointLight();
		void ilumina(int i);
};