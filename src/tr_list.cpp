/*
 * tr_list.cpp
 *
 *  Created on: Apr 17, 2013
 *      Author: ivo
 */

#include"tr_list.h"

bool is_lesser(transition& t1, transition& t2);
int newSize(int& current);

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
	last = -1;
	n = 0;
}

void TransitionsList::copyFrom(TransitionsList& l) {
	n = l.n;
	store = new transition*[n];
	for (last=0; last<=l.last; last++) {
		store[last] = l.store[last];
	}
}

void TransitionsList::deleteList() {
	for (int i=0; i<=last; i++) {
		delete store[i];
	}
	delete[] store;
}

void TransitionsList::add(transition& el) {
	if(last == n - 1 || n == 0) {
		n = newSize(n);
		transition** newStore = new transition*[n];
		for (int i=0; i<=last; i++) {
			newStore[i] = store[i];
		}
		delete[] store;
		store = newStore;
	}
	int i;
	// Find the index, at which the new element should be inserted.
	// Sort should be in ascending order by the integer value of the char.
	for (i=0; i<=last; i++) {
		if(!is_lesser(get(i), el)) {
			break;
		}
	}
	// Shift all greater elements to the right.
	for (int k=last; k>=i; k--) {
		store[k+1] = store[k];
	}
	store[i] = new transition(el);
	// An element was added.
	last++;
	for (int i=0; i<last; i++) {
		if (store[i] == store[i+1])
			break;
	}
}

transition& TransitionsList::get(int i) {
	if(i >= n) {
		throw 2;
	}
	return *store[i];
}

void TransitionsList::remove(int i) {
	delete store[i];
	for (int k=i; k<last; k++) {
		store[k] = store[k+1];
	}
	last--;
}

int TransitionsList::size() {
	return last+1;
}

bool is_lesser(transition& t1, transition& t2) {
	if (t1.ch < t2.ch) {
		return true;
	} else if (t1.ch > t2.ch) {
		return false;
	} else {
		return t1.dest < t2.dest;
	}
}

int newSize(int& current) {
	if(current <= 0)
		return 5;
	return current * 2;
}
