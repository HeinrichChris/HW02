#include "Shape.h"

class DNode {
public:
	DNode();

	void addNext(DNode, DNode);
	void remove();

	// this part is bad programming style, but the assignment itself asks for bad style.
	// I would not put class variables as public outside of this assignment.
	DNode* next;
	DNode* prev;
	Shape* shape;

	void reverse();
	void reverseAll(); // only to be called by sentinel node

	void draw();
	void drawAll(); // only to be called by sentinel node

	//void updateAll(); // only to be called by sentinel node

	bool isEmpty();
};