#include "Shape.h"

class Player{
public:
	Player();
	bool collision(Shape*);
	void update();
	void draw();
	int getX();
	int getY();
private:
	int x;
	int y;
	int radius;
};