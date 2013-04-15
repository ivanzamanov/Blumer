/*
 * tests.cpp
 *
 *  Created on: Apr 15, 2013
 *      Author: ivo
 */

#include"tests.h"
#include"automata.h"

void test_table_expansion();
void test_entry_expansion();

void run_tests() {
	test_entry_expansion();
	test_table_expansion();
}

void test_table_expansion() {
	automaton a;
	expand_states(a);
	expand_table(a);
	printf("States size: %d", a.states_size);
	printf("Table size: %d", a.table_size);
}

void test_entry_expansion() {

}
