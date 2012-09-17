#pragma once

#include "cinder/app/AppBasic.h"

class Shape{
public:
	Shape();

	void draw();

	int* getLoc();
	void setX(int);
	void setY(int);
	void setZ(int);
	void setVelocityX(int);
	void setVelocityY(int);
	void setVelocityZ(int);

	int getType();
	void collision(Shape*);

	int getHP();
	void setHP(int);

	void update();

protected:
	int x;
	int y;
	int z;
	int radius;

	int velX;
	int velY;
	int velZ;

	uint8_t* color;

	int hp;
	int type;
};