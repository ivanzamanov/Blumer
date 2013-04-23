/*
 * utilities.cpp
 *
 *  Created on: Apr 24, 2013
 *      Author: ivo
 */

#include"utils.h"
#include<cstring>

int newListSize(int& current) {
	if (current <= 0)
		return 5;
	return current * 2;
}

char* substring(char* str, int start, int size) {
	char* sub = new char[size];
	strncpy(sub, str, size);
	return str;
}
