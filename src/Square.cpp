#include "Square.h"

Square::Square(){
	init();

	type = 2;

	radius = 10;

	color[0] = 255;
	color[1] = 0;
	color[2] = 255;
}

void Square::draw(){
	glColor3f(color[0], color[1], color[2]);

	// begin OpenGL drawing
	glBegin(GL_QUADS);

	// assign vertices for OpenGL
	glVertex2f(x-radius, y-radius);
	glVertex2f(x-radius, y+radius);
	glVertex2f(x+radius, y-radius);
	glVertex2f(x+radius, y+radius);

	// end vertex assignment
	glEnd();
}

void Square::collision(Shape* shape){
	int xVelocityChange = 10;
	int yVelocityChange = 30;

	// shape type 4 = rain
	if((*shape).getType() == 4){
		// we only care about y-direction here
		if((*shape).getLoc()[1] <= y + radius &&
			(*shape).getLoc()[1] >= y - radius){
				// bounce the rain up a bit and give it a random x velocity
				shape->setVelocityY(yVelocityChange);
				shape->setVelocityX(rand() % 30);

				hp--;
				shape->setHP((shape->getHP()) - 1);
		}
		// now worry about x-direction
		else if((*shape).getLoc()[1] <= y + radius &&
			(*shape).getLoc()[1] >= y - radius &&
			((*shape).getLoc()[0] >= x - radius ||
			(*shape).getLoc()[0] <= x + radius)){
				// bounce the rain off in the x direction
				if((*shape).getLoc()[0] >= x - radius){
					shape->setVelocityX(-1 * xVelocityChange);
				}
				else{
					shape->setVelocityX(xVelocityChange);
				}

				hp--;
				shape->setHP((shape->getHP()) - 1);
		}
	}
}