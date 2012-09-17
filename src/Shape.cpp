#include "Shape.h"

Shape::Shape(){
	x = y= z = 0;
	velX = velY = velZ = 0;
	
	color = new uint8_t[3];
	color[0] = color[1] = color[2] = 255;

	hp = 100;
	type = -1;
}

int Shape::getHP(){
	return hp;
}

int Shape::getType(){
	return type;
}

int* Shape::getLoc(){
	int loc[3] = {x,y,z};
	return loc;
}

void Shape::setHP(int newHP){
	hp = newHP;
}

void Shape::setX(int newX){
	x = newX;
}

void Shape::setY(int newY){
	y = newY;
}

void Shape::setZ(int newZ){
	z = newZ;
}

void Shape::setVelocityX(int newVel){
	velX = newVel;
}

void Shape::setVelocityY(int newVel){
	velY = newVel;
}

void Shape::setVelocityZ(int newVel){
	velZ = newVel;
}

void Shape::update(){
	x += velX;
	y += velY;
	z += velZ;

	if(type == 4){
		velY -= 5;
	}
	else{
		color[0] = color[2] = 255 * (int)(hp / 100.0);
	}
}

void Shape::draw(){
	if(type == 1){
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
	else if(type == 2){
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
	else{
		// set color
		glColor3f(color[0], color[1], color[2]);
		// begin OpenGL drawing
		glBegin(GL_POINTS);
		glVertex2f(x, y);
		glEnd();
	}
}

void Shape::collision(Shape* shape){
	if(type==1){
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
	else if(type==2){
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


}