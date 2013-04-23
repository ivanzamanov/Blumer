/*
 * build.h
 *
 *  Created on: Apr 16, 2013
 *      Author: ivo
 */

#ifndef BUILD_H_
#define BUILD_H_

#include"automata.h"

void build_thompson(automaton& a, char* regex);

void build_berry_setti(automaton& a, char* regex);


#endif /* BUILD_H_ */
