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
