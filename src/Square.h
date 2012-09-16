#include "Shape.h"

class Square : Shape {
public:
	Square();
	void draw();
	void collision(Shape*);
private:
	int radius; // distance to go out from center in x or y directions
};