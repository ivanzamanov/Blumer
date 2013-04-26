/*
 * build.cpp
 *
 *  Created on: Apr 16, 2013
 *      Author: ivo
 */

#include"queue.h"
#include"stack.h"
#include"build.h"
#include"automata.h"
#include"states_list.h"
#include"utils.h"

#include<stdio.h>
#include<string.h>

struct temp_automaton {
	StatesList states;
	int states_size;
	transition* transitions;
	int transitions_size;
};

void build_bs_helper(temp_automaton& a, char* regex);
void build_bs_char(temp_automaton& a, char c);

void concat(temp_automaton& pre, temp_automaton& post);
void logical_or(temp_automaton& pre, temp_automaton& post);
void star(temp_automaton& a);

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
	// TODO: Compress tmp into a.
}

void add_queue(Stack<Queue<temp_automaton>>& s) {
	Queue<temp_automaton> q;
	temp_automaton a;
	q.push(a);
	s.push(q);
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
void build_bs_helper(temp_automaton& a, char* regex) {
	if (regex == 0) {
		return;
	}
	Stack<Queue<temp_automaton>> s;
	add_queue(s);
	int i = 0;
	while (regex[i] != 0) {
		if (regex[i] == '(') {
			add_queue(s);
		} else if (regex[i] == ')') {
			i++; // Because of the *
			Queue<temp_automaton> q;
			s.pop(q);
			temp_automaton first;
			q.pop(first);
			while (!q.isEmpty()) {
				temp_automaton next;
				q.pop(next);
				concat(first, next);
			}
		} else {
			// Concatenate regex[i] to s.peek().peek_last(),
			// i.e. to the last automaton.
			temp_automaton a;
			build_bs_char(a, regex[i]);
			concat(s.peek().peek_last(), a);
		}
		i++;
	}
}

void concat(temp_automaton& pre, temp_automaton& post) {

}

void logical_or(temp_automaton& pre, temp_automaton& post) {

}

void star(temp_automaton& a) {
	// Make "a" a star of itself.
}

void build_bs_char(temp_automaton& a, char ch) {
	printf("Char: %c\n", ch);
	state start_state, final_state;
	start_state.first_ch = ch;
	start_state.start = -ch;

	final_state.isFinal = true;
	a.states.add(start_state);
	a.states.add(final_state);
}
