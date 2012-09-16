#include "DoubleLinkedList.h"

void DNode::addNext(DNode node){
	next->prev = &node;
	node.next = next;
	next = &node;
	node.prev = this;
}

void DNode::addPrev(DNode node){
	prev->next = &node;
	node.prev = prev;
	node.next = this;
	prev = &node;
}

void DNode::remove(){
	prev->next = next;
	next->prev = prev;

	delete(next);
	delete(prev);
	delete(shape);
}

void DNode::reverse(){
	DNode* temp = next;
	next = prev;
	prev = temp;
}

void DNode::reverseAll(){
	DNode* current = next;

	while(current != this){
		current->reverse();
		current = current->prev;
	}

	delete(current);
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

void DNode::updateAll(){
	DNode* current = next;

	while(current != this){
		current->shape->update();
		current = current->next;
	}
}