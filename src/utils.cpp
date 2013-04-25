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

char* substring(char* str, int start, int end) {
	int size = end - start;
	char* sub = new char[size+1];
	strncpy(sub, str+start, size);
	sub[size] = 0;
	return sub;
}
