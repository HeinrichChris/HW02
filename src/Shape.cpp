#include "Shape.h"
#include "cinder\gl\gl.h"

using namespace ci;

Shape::Shape(){
	x = y= z = 0;
	velX = velY = velZ = 0;
	
	color = new uint8_t[3];
	color[0] = 255;
	color[1] = 255;
	color[2] = 255;

	hp = 50;
	type = -1;
	radius = 10;
}

void Shape::square(){
	type = 2;

	radius = 10;

	color[0] = 255;
	color[1] = 0;
	color[2] = 255;
}

void Shape::rain(){
	color[0] = 0;
	color[1] = 100;
	color[2] = 255;

	type = 4;

	hp = 5;
	x = 100 + rand() % 300;
	y = 100 ;

	velX = 0;
	velY = 0;
}

void Shape::circle(){
	type = 1;

	radius = 10;

	color[0] = 255;
	color[1] = 0;
	color[2] = 255;
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
	if(type > 0){
		x += velX;
		y += velY;
		z += velZ;

		if(y > 800){
			y = 0;
			velY = 0;
		}

		if(type == 4){
			if(velY < 10){
				velY += 1;
			}
		}
		else{
			color[0] = (int)(255.0 * (hp / 100.0));
			color[2] = color[0];
		}
	}
}

void Shape::draw(){
	if(type == 1){
		// begin OpenGL drawing
		gl::color(color[0], color[1], color[2]);
		// begin OpenGL drawing
		gl::drawSolidCircle(Vec2f(x,y),radius);

	}
	else if(type == 2){
		gl::color(color[0], color[1], color[2]);
		// begin OpenGL drawing
		gl::drawSolidRoundedRect(Rectf(x-radius, y-radius, x+radius, y+radius),5.0f);

	}
	else{
		// set color
		gl::color(color[0], color[1], color[2]);
		// begin OpenGL drawing
		gl::drawSolidCircle(Vec2f(x,y),5.0f);
	}
}

void Shape::collision(Shape* shape){
	if(type==1){
		if(shape->getType() == 4){
			int distance = sqrt(pow(((double)(shape->getLoc()[0] - x)),2) + pow(((double)(shape->getLoc()[1] - y)),2));
			if(distance <= radius){
				shape->setVelocityX(shape->getLoc()[0] - x);
				shape->setVelocityY(-30); // This is not physically correct, but I want the rain to bounce up regardless of position

				hp--;
				shape->setHP((shape->getHP()) - 1);
			}
		}

	}
	else if(type==2){
		int xVelocityChange = -5;
		int yVelocityChange = -5;

		// shape type 4 = rain
		if((*shape).getType() == 4){
			// we only care about y-direction here
			if((*shape).getLoc()[1] <= y + radius &&
				(*shape).getLoc()[1] >= y - radius){
					// bounce the rain up a bit and give it a random x velocity
					shape->setVelocityY(yVelocityChange);
					shape->setVelocityX(rand() % 5);

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