/*
 * automata.h
 *
 *  Created on: Apr 14, 2013
 *      Author: ivo
 */

#ifndef AUTOMATA_H_
#define AUTOMATA_H_

struct entry {
	int source;
	int ch;
	int dest;
	int offset;
};

typedef entry* tarjantable ;

/*!
 * Represents a single transition in the automata.
 */
struct transition {
	int source;
	int ch;
	int dest;
};

/*!
 * Represents a single state of the automata.
 */
struct state {
	int start;
	int first_ch;
	int isFinal;
};

/*!
 * Represents an automaton.
 */
struct automaton {
	tarjantable* table;
	int table_size;
	int last_state;
	state* states;
	int states_size;
};

/*!
 * Locates the first index, which is suitable for a "start" field of a state with transitions "transitions"
 * @param table
 * @param table_size
 * @param transitions
 * @param transitions_size
 * @return
 */
int first_admisable_position(tarjantable table, int table_size, transition* transitions, int transitions_size);

/*!
 * Inserts the specified transitions array for the given state into the given table.
 * @param pos
 * @param table
 * @param table_size
 * @param source_state
 * @param transitions
 * @param transitions_size
 */
void insert_transitions(int pos, tarjantable table, int table_size, transition* transitions, int transitions_size);

/*!
 * Create a new state in the given automaton with the specified outgoing transitions.
 * @param a
 * @param tr
 * @param tr_size
 */
state new_state(automaton& a, transition* tr, int tr_size);

/*!
 * Returns true if there is a transition with the given character from the specified state in the automaton.
 * @param a
 * @param source
 * @param ch
 * @param dest
 * @return
 */
bool has_transition(automaton& a, int source, int ch);

#endif /* AUTOMATA_H_ */
