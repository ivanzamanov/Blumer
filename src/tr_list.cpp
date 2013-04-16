/*
 * tr_list.cpp
 *
 *  Created on: Apr 17, 2013
 *      Author: ivo
 */

#include"tr_list.h"

node* createNode(transition& tr);
bool is_lesser(transition& t1, transition& t2);

TransitionsList::TransitionsList() {

}

TransitionsList::TransitionsList(TransitionsList& l) {
	copyFrom(l);
}

TransitionsList& TransitionsList::operator=(TransitionsList& l) {
	deleteList();
	copyFrom(l);
	return *this;
}

TransitionsList::~TransitionsList() {
	deleteList();
}

void TransitionsList::copyFrom(TransitionsList& l) {
	if (l.size <= 0)
		return;

	this->size = l.size;
	node* h2 = l.head;
	this->head = createNode(*(head->data));
	node* last_node = this->head;
	for (int i = 1; i < l.size; i++) {
		h2 = h2->next;
		node* new_node = createNode(*(h2->data));
		new_node->prev = last_node;
		last_node->next = new_node;
		last_node = new_node;
	}
}

void TransitionsList::deleteList() {
	while (this->head != 0) {
		node* next = this->head->next;
		delete this->head;
		this->head = next;
	}
}

void TransitionsList::add(transition& el) {
	if (head == 0) {
		head = createNode(el);
	} else {
		node* after = head;
		while(after != 0 && is_lesser(el, *after->data)) {

		}
	}
}

/*!
 * TODO: Refactor so this won't be O(n) every time.
 */
transition& TransitionsList::get(int i) {
	if (i >= size) {
		throw 1;
	} else if (i == size - 1) {
		return *(tail->data);
	} else {
		node* current = this->head;
		for (int k = 1; k < i; k++) {
			current = current->next;
		}
		return *(current->data);
	}
}

node* createNode(transition& tr) {
	node* result = new node;
	result->data = &tr;
	return result;
}

bool is_lesser(transition& t1, transition& t2) {
	if(t1.ch < t2.ch) {
		return true;
	} else if (t1.ch > t2.ch) {
		return false;
	} else {
		return t1.dest < t2.dest;
	}
}
