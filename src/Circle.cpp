#include "Circle.h"
#include <math.h>

Circle::Circle(){
	init();

	type = 1;

	radius = 10;

	color[0] = 255;
	color[1] = 0;
	color[2] = 255;
}

void Circle::draw(){
	glColor3f(color[0], color[1], color[2]);

	// begin OpenGL drawing using triangles
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y);

	// I used double because of the sin/cos methods requiring double
	for(double i = 0; i < 360; i+=5){
		glVertex2f(x + sin(i) * radius, y + cos(i) * radius);
	}

	glEnd();
}

void Circle::collision(Shape* shape){
	// if shape is rain, then perform collision
	if(shape->getType() == 4){
		int distance = sqrt(pow(((double)(shape->getLoc()[0] - x)),2) + pow(((double)(shape->getLoc()[1] - y)),2));
		if(distance <= radius){
			shape->setVelocityX(shape->getLoc()[0] - x);
			shape->setVelocityY(30); // This is not physically correct, but I want the rain to bounce up regardless of position

			hp--;
			shape->setHP((shape->getHP()) - 1);
		}
	}

}