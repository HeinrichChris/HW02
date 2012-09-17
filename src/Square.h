#include "Shape.h"

class Square : Shape {
public:
	Square();
	void draw();
	void collision(Shape*);
};