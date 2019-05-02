#include "Luz.h"

class Spot: public Luz
{
public: float angle;

		Spot();
		Spot(float x, float y, float z, float angle);
		~Spot();
};
