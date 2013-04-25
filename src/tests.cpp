/*
 * tests.cpp
 *
 *  Created on: Apr 15, 2013
 *      Author: ivo
 */

#include"stack.h"
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

void run_tests() {
	test_entry_expansion();
	test_table_expansion();
	test_automaton_eval();
	test_list();
	test_bs_build();
	test_stack();
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

void test_bs_build() {
	char* regex = (char*)"(reg)*";
	automaton a;
	build_berry_setti(a, regex);
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
