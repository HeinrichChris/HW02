#include "Shape.h"

void Shape::init(){
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