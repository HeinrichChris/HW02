#include "Circle.h"
#include <math.h>

Circle::Circle(){
	Shape();

	type = 1;

	radius = 10;

	color[0] = 255;
	color[1] = 0;
	color[2] = 255;
}