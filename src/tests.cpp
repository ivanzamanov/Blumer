/*
 * tests.cpp
 *
 *  Created on: Apr 15, 2013
 *      Author: ivo
 */

#include"stack.h"
#include"queue.h"
#include"tests.h"
#include"automata.h"
#include"stdio.h"
#include"tr_list.h"
#include"build.h"

void test_table_expansion();
void test_entry_expansion();
void test_automaton_eval();
void test_list();
void test_bs_build();
void test_stack();
void test_queue();

void run_tests() {
	test_entry_expansion();
	test_table_expansion();
	test_automaton_eval();
	test_list();
	test_bs_build();
	test_stack();
	test_queue();
}

void test_table_expansion() {
	automaton a;
	expand_table(a);
	printf("Table size: %d\n", a.table_size);
}

void test_entry_expansion() {
	automaton a;
	expand_states(a);
	printf("States size: %d\n", a.states_size);
}

void test_automaton_eval() {
	automaton a;
}

void test_list() {
	TransitionsList list;
	int N = 50;
	for (int i = 0; i < N; i++) {
		transition tr;
		tr.ch = N - i;
		list.add(tr);
	}
	for (int i = 0; i < N; i++) {
		transition tr;
		tr.ch = N + i + 1;
		list.add(tr);
	}
	for (int i = 0; i < list.size() - 1; i++) {
		if (list.get(i).ch > list.get(i + 1).ch)
			printf("Incorrect ordering\n");
	}
	for (int i = 0; i < N/2; i++) {
		list.remove(i);
	}
	for (int i = 0; i<list.size(); i++) {
		transition& tr = list.get(i);
		if(list.lookupChar(tr.ch) != i) {
			printf("Search is wrong - i=%d, ch=%d\n", i, (int)tr.ch);
			break;
		}
	}
}

/*
 * Idea for implementing parsing:
 * Stack of lists of automatons.
 * For every character in the regex:
 * - if char == (, then push in another list
 * - if char == ), then pop a list, create union
 * of all automatons in the popped list, char++,
 * add the resulting automaton to the list at the head
 * - if char == |, then add a new automaton to the list
 * - otherwise, concatenate char to the last automaton
 * in the current list
 *
 * Time: O(strlen(regex)), which should be minimal.
 */
void test_bs_build() {
	char* regex = (char*)"(reg)*";
//	automaton a;
//	build_berry_setti(a, regex);

	Stack<automaton> s;
	int i=0;
	while(regex[i] != 0) {
		if(regex[i] == '(') {
			automaton a;
			s.push(a);
		} else if (regex[i] == ')') {
			i++; // Because of the *
			automaton a;
			s.pop(a);
		} else {
			// Concatenate regex[i] to s.peek(a).
		}
		i++;
	}
}

void test_stack() {
	Stack<int> s;
	for (int i=0; i<10; i++) {
		s.push(i);
	}
	while(!s.isEmpty()) {
		int i;
		s.pop(i);
	}
}

void test_queue() {
	Queue<int> s;
	for (int i=0; i<10; i++) {
		s.push(i);
	}
	while(!s.isEmpty()) {
		int i;
		s.pop(i);
	}
}
