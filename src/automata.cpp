/*
 * automata.c
 *
 *  Created on: Apr 15, 2013
 *      Author: ivo
 */

#include "automata.h"

bool is_admissable_position(int i, tarjantable table, int table_size,
		transition* transitions, int transitions_size);

int first_admisable_position(tarjantable table, int table_size,
		transition* transitions, int transitions_size) {
	int pos = 0;
	while(!is_admissable_position(pos, table, table_size, transitions, transitions_size)) {
		pos++;
	}
	return pos;
}

bool is_admissable_position(int pos, tarjantable table, int table_size,
		transition* transitions, int transitions_size) {
	for (int i = 0; i < transitions_size; i++) {
		int transition_dest = pos + transitions[i].ch;
		if (transition_dest < table_size
				&& table[transition_dest].ch < 0) {
			return false;
		}
	}
	return true;
}

void insert_transitions(int pos, tarjantable table, int table_size, transition* transitions, int transitions_size) {
	for (int i=0; i < transitions_size; i++) {
		table[i].ch = transitions[i].ch;
		table[i].source = transitions[i].source;
		table[i].dest = transitions[i].dest;
		table[i].offset = pos;
	}
}

const int ENTRIES_EXPAND_FACTOR = 2;
void expand_table(automaton& a) {
	tarjantable old_table = a.table;
	int old_size = a.table_size;
	int to_size = ENTRIES_EXPAND_FACTOR * old_size;
	a.table = new entry[to_size];
	for (int i=0; i<old_size; i++) {
		a.table[i] = old_table[i];
	}
}

const int STATES_EXPAND_FACTOR = 2;
void expand_states(automaton& a) {
	state* old_states = a.states;
	int old_size = a.states_size;
	int to_size = ENTRIES_EXPAND_FACTOR * old_size;
	a.states = new state[to_size];
	for (int i=0; i<old_size; i++) {
		a.states[i] = old_states[i];
	}
}

state& new_state(automaton& a, transition* tr, int tr_size) {
	if (a.states[a.states_size-1].first_ch >= 0) {
		expand_states(a);
	}
	a.last_state++;
	return a.states[a.last_state];
}
