#include "Player.h"

Player::Player(){
	x = 0;
	y = 0;
	radius = 5;
}

bool Player::collision(Shape* shape){
	// we only care about y-direction here
	if(((*shape).getLoc()[1] <= y + radius &&
		(*shape).getLoc()[1] >= y - radius) || 
		(*shape).getLoc()[1] <= y + radius &&
		(*shape).getLoc()[1] >= y - radius &&
		((*shape).getLoc()[0] >= x - radius ||
		(*shape).getLoc()[0] <= x + radius)){
			return true;
	}
	// now worry about x-direction
	else{
		return false;
	}
}

int Player::getX(){
	return x;
}

int Player::getY(){
	return y;
}

// is this needed?
void update(){

}

void draw(){
	uint8_t color[3] = {255, 255, 0};

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