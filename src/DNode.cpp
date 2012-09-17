#include "DoubleLinkedList.h"

/**
* This is the constructor for DNode
*/
DNode::DNode(){
	next = prev = this;
	next->prev = this;
	shape = new Shape();
}

/**
* This method checks if the list only contains a sentinel node
*/
bool DNode::isEmpty(){
	if(this->next == this){
		return true;
	}

	return false;
}

/**
* This adds another node to the end of the node specified.
* @param node The node to be added
* @param thisNode The node that gains a new node following it
*/
void DNode::addNext(DNode node, DNode thisNode){
		node.next = thisNode.next;
		node.prev = &thisNode;
		thisNode.next->prev = &node;
		thisNode.next = &node;
}

/**
* This resets the rain data when it would be otherwise destroyed.
*/
void DNode::remove(){
	shape->rain();
	/* this is how you would actually remove it
	prev->next = next;
	next->prev = prev;
	*/
}

/**
* This reverses the linked list node
*/
void DNode::reverse(){
	DNode* temp = next;
	next = prev;
	prev = temp;
}

/**
* This reverses the whole linked list
*/
void DNode::reverseAll(){
	DNode* current = prev;

	while(current != this){
		current->reverse();
		current = current->next;
	}

}

/**
* This draws the shape for a DNode
*/
void DNode::draw(){
	shape->draw();
}

/**
* This calls draw() on a whole list
*/
void DNode::drawAll(){
	DNode* current = next;

	while(current != this){
		current->draw();
		current = current->next;
	}
}