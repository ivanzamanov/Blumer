/*
 * build.cpp
 *
 *  Created on: Apr 16, 2013
 *      Author: ivo
 */

#include"build.h"
#include"automata.h"
#include<string.h>

struct temp_automaton {
	state* states;
	int states_size;
	transition* transitions;
	int transitions_size;
};

void concat(automaton& a, char* regex);
void star(automaton& a);
void logical_or(automaton& a);

/*!
 * 	Basic idea is the following - first build it as a simple graph
 * 	and after that compress it into a tarjantable.
 * 	Building the graph:
 * 	Array for the states, reorder so starting state(s) is in the beginning
 * 	and final states are near the end.
 * 	While building - array of lists containing available outgoing transitions.
 */

void berry_setti(automaton& a, char* regex) {
	int len = strlen(regex);
	temp_automaton tmp;
	tmp.states = new state[len];

}

void concat(automaton& a, char* regex) {

}
