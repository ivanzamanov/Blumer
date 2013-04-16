/*
 * automata.h
 *
 *  Created on: Apr 14, 2013
 *      Author: ivo
 */

#ifndef AUTOMATA_H_
#define AUTOMATA_H_

struct entry {
	int source = -1;
	int ch = -1;
	int dest = -1;
	int offset = -1;
};

typedef entry* tarjantable ;

/*!
 * Represents a single transition in the automata.
 */
struct transition {
	int source = -1;
	int ch = -1;
	int dest = -1;
};

/*!
 * Represents a single state of the automata.
 */
struct state {
	int start = -1;
	int first_ch = -1;
	int isFinal = 0;
};

/*!
 * Represents an automaton.
 */
struct automaton {
	tarjantable table = 0;
	int table_size = 0;
	int last_state = -1;
	state* states = 0;
	int states_size = 0;
};

/*!
 * Locates the first index, which is suitable for a "start" field of a state with transitions "transitions"
 */
int first_admisable_position(tarjantable table, int table_size, transition* transitions, int transitions_size);

/*!
 * Inserts the specified transitions array for the given state into the given table.
 */
void insert_transitions(int pos, tarjantable table, int table_size, transition* transitions, int transitions_size);

/*!
 * Create a new state in the given automaton with the specified outgoing transitions.
 */
state& new_state(automaton& a, transition* tr, int tr_size);

/*!
 * Returns true if there is a transition with the given character from the specified state in the automaton.
 */
bool has_transition(automaton& a, int source, int ch);

/*!
 * Expand the size of the given automaton's entry table.
 */
void expand_table(automaton& a);

/*!
 * Expand the size of the given automaton's state array.
 */
void expand_states(automaton& a);

/*!
 * Creates an empty automaton.
 */
void create_automaton(automaton*& a);

#endif /* AUTOMATA_H_ */
