/*
 * build.cpp
 *
 *  Created on: Apr 16, 2013
 *      Author: ivo
 */

#include"build.h"
#include"automata.h"
#include"states_list.h"
#include"utils.h"
#include<string.h>

struct temp_automaton {
	StatesList states;
	int states_size;
	transition* transitions;
	int transitions_size;
};

void build_bs_helper(temp_automaton& a, char* regex);
void build_bs_char(temp_automaton& a, char c);

void concat(temp_automaton& pre, char* regex);
void star(temp_automaton& a);
void logical_or(temp_automaton& pre, char* regex);

/*!
 * 	Basic idea is the following - first build it as a simple graph
 * 	and after that compress it into a tarjantable.
 * 	Building the graph:
 * 	Array for the states, reorder so starting state(s) is in the beginning
 * 	and final states are near the end.
 * 	While building - array of lists containing available outgoing transitions.
 */

void build_berry_setti(automaton& a, char* regex) {
	temp_automaton tmp;
	build_bs_helper(tmp, regex);
	// Compress tmp into a.
}

void build_bs_helper(temp_automaton& a, char* regex) {
	if (regex == 0) {
		return;
	}
	int len = strlen(regex);
	if (len == 0) {
		state only_state;
		only_state.first_ch = 0;
		only_state.isFinal = true;
		only_state.start = -1;
		a.states.add(only_state);
		return;
	} else if (len == 1) {
		build_bs_char(a, regex[0]);
		return;
	} else if (len >= 3 && regex[0] == '('
						&& regex[len - 1] == '*'
						&& regex[len - 2] == ')') {
		int sublen = len - 3;
		char* sub = substring(regex, 1, sublen);
		strncpy(sub, regex, sublen);
		build_bs_helper(a, sub);
		delete sub;
		star(a);
	} else {
		int index;
		for (index = 0; index < len; index++) {
			if (regex[index] == '|')
				break;
		}
		if (index == len) {
			char* sub = substring(regex, 1, len);
			concat(a, sub);
			delete sub;
			build_bs_helper(a, regex + 1);
		} else {
			// TODO: logical "or" on both sides of the |
		}
	}
}

void concat(temp_automaton& pre, char* regex) {
	automaton post;
	build_berry_setti(post, regex);
	// Concatenate post to pre.
}

void logical_or(temp_automaton& a1, char* regex) {
	automaton a2;
	build_berry_setti(a2, regex);
	// Do "or" between a1 and a2
}

void star(temp_automaton& a) {
	// Make "a" a star of itself.
}

void build_bs_char(temp_automaton& a, char ch) {
	state start_state, final_state;
	start_state.first_ch = ch;
	start_state.start = -ch;

	final_state.isFinal = true;
	a.states.add(start_state);
	a.states.add(final_state);
}
