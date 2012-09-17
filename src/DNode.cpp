#include "DoubleLinkedList.h"

DNode::DNode(){
	next = prev = this;
	next->prev = this;
	shape = new Shape();
}

bool DNode::isEmpty(){
	if(this->next == this){
		return true;
	}

	return false;
}

void DNode::addNext(DNode node, DNode thisNode){
		node.next = thisNode.next;
		node.prev = &thisNode;
		thisNode.next->prev = &node;
		thisNode.next = &node;
}

void DNode::remove(){
	shape->rain();
	/* this is how you would actually remove it
	prev->next = next;
	next->prev = prev;
	*/
}

void DNode::reverse(){
	DNode* temp = next;
	next = prev;
	prev = temp;
}

void DNode::reverseAll(){
	DNode* current = prev;

	while(current != this){
		current->reverse();
		current = current->next;
	}

}

void DNode::draw(){
	shape->draw();
}

void DNode::drawAll(){
	DNode* current = next;

	while(current != this){
		current->draw();
		current = current->next;
	}
}