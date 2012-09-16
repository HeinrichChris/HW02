#include "Shape.h"

class Circle : Shape {
public:
	Circle();
	void draw();
	void collision(Shape*);
private:
	int radius;
}