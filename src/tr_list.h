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
	TransitionsList(const TransitionsList& l);
	~TransitionsList();
	const TransitionsList& operator=(const TransitionsList& l);

	void add(const transition& el);
	transition& get(int i);
	void remove(int i);
	int size();
	int lookup(char c);

private:
	void copyFrom(const TransitionsList& l);
	void deleteList();
	transition** store = 0;
	int n = 0;
	int last = -1;
};

#endif /* LIST_H_ */
