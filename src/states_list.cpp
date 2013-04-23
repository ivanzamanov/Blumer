/*
 * states_list.cpp
 *
 *  Created on: Apr 24, 2013
 *      Author: ivo
 */

#include"states_list.h"
#include"utils.h"

StatesList::StatesList() {

}

StatesList::StatesList(const StatesList& l) {
	copyFrom(l);
}

const StatesList& StatesList::operator=(const StatesList& l) {
	deleteList();
	copyFrom(l);
	return *this;
}

StatesList::~StatesList() {
	deleteList();
	last = -1;
	n = 0;
}

void StatesList::copyFrom(const StatesList& l) {
	n = l.n;
	store = new state*[n];
	for (last = 0; last <= l.last; last++) {
		store[last] = l.store[last];
	}
}

void StatesList::deleteList() {
	for (int i = 0; i <= last; i++) {
		delete store[i];
	}
	delete[] store;
}

void StatesList::add(const state& el) {
	if (last == n - 1 || n == 0) {
		n = newListSize(n);
		state** newStore = new state*[n];
		for (int i = 0; i <= last; i++) {
			newStore[i] = store[i];
		}
		delete[] store;
		store = newStore;
	}
	store[last+1] = new state(el);
	last++;
}

state& StatesList::get(int i) {
	if (i >= n) {
		throw "Range check failed, requested index is greater that size";
	}
	return *store[i];
}

void StatesList::remove(int i) {
	delete store[i];
	for (int k = i; k < last; k++) {
		store[k] = store[k + 1];
	}
	last--;
}

int StatesList::size() {
	return last + 1;
}
