#include "Shape.h"

class Rain : Shape{
public:
	Rain();
	void draw();
	void collision(Shape*) = 0;
	void update();
};