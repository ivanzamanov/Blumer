/*
 * list.h
 *
 *  Created on: Apr 16, 2013
 *      Author: ivo
 */

#ifndef LIST_H_
#define LIST_H_

#include"automata.h"

using namespace std;

struct node {
	node* prev = 0;
	node* next = 0;
	transition* data = 0;
};

/*!
 * A list of transitions, which are being sorted while inserting by their character.
 */
class TransitionsList {
public:
	TransitionsList();
	TransitionsList(TransitionsList& l);
	~TransitionsList();
	TransitionsList& operator=(TransitionsList& l);

	void add(transition& el);
	transition& get(int i);
	void remove(int i);
	int size();

private:
	void copyFrom(TransitionsList& l);
	void deleteList();
	transition** store = 0;
	int n = 0;
	int last = -1;
};

#endif /* LIST_H_ */
