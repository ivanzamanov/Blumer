/*
 * list.h
 *
 *  Created on: Apr 16, 2013
 *      Author: ivo
 */

#ifndef LIST_H_
#define LIST_H_

#include"automata.h"

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
	int lookupChar(char c);
	int lookupState(int s);

private:
	void copyFrom(const TransitionsList& l);
	void deleteList();
	transition** store = 0;
	int n = 0;
	int last = -1;
};

#endif /* LIST_H_ */
