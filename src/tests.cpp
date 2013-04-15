/*
 * tests.cpp
 *
 *  Created on: Apr 15, 2013
 *      Author: ivo
 */

#include"tests.h"
#include"automata.h"
#include"stdio.h"

void test_table_expansion();
void test_entry_expansion();

void run_tests() {
	test_entry_expansion();
	test_table_expansion();
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
