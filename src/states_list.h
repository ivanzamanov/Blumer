/*
 * states_list.h
 *
 *  Created on: Apr 24, 2013
 *      Author: ivo
 */

#ifndef STATES_LIST_H_
#define STATES_LIST_H_

#include"automata.h"

class StatesList {
public:
	StatesList();
	StatesList(const StatesList& l);
	~StatesList();
	const StatesList& operator=(const StatesList& l);

	void add(const state& el);
	state& get(int i);
	void remove(int i);
	int size();

private:
	void copyFrom(const StatesList& l);
	void deleteList();
	state** store = 0;
	int n = 0;
	int last = -1;
};



#endif /* STATES_LIST_H_ */
