#include "Rain.h"

Rain::Rain(){
	init();

	color[0] = 0;
	color[1] = 100;
	color[2] = 255;

	type = 4;

	hp = 5;
}

void Rain::draw(){
	// set color
	glColor3f(color[0], color[1], color[2]);
	// begin OpenGL drawing
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}

void Rain::update(){
	x += velX;
	y += velY;
	z += velZ;

	if(velY > 5){
		velY--;
	}
}

void Rain::collision(Shape* shape){
	// do nothing
}