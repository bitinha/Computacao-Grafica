#include <stdio.h>
#include <cstdlib>
#include "Cone.h"


int main(int argc, const char* argv[]) {
	printf("ola\n");
	float f = 1;
	if(argc > 1){
		f = std::atof(argv[1]);
	}
	Cone c = Cone(f,2,1,1);
	printf("%f",c.getRadius());
	return 0;

}