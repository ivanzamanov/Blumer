/*
 * stack.h
 *
 *  Created on: Apr 26, 2013
 *      Author: ivo
 */

#ifndef STACK_H_
#define STACK_H_

template<class T>
struct stack_node {
	T* data = 0;
	stack_node* prev = 0;
};

template<class T>
class Stack {
public:
	Stack<T>();
	Stack<T>(const Stack& s);
	const Stack<T>& operator=(const Stack<T>& s);
	virtual ~Stack<T>();

	virtual void push(const T& el);
	virtual void pop(T& returned);
	virtual void peek(T& returned);
	virtual bool isEmpty();

private:
	stack_node<T>* head=0;
};

template<class T>
Stack<T>::Stack() {

}

template<class T>
Stack<T>::Stack(const Stack<T>& s) {
	stack_node<T>* next = s.head;
	while(next != 0) {
		push(next->data);
	}
}

template<class T>
Stack<T>::~Stack() {
	stack_node<T>* node = this->head;
	while(node != 0) {
		delete node->data;
		node = node->prev;
	}
}

template<class T>
const Stack<T>& Stack<T>::operator =(const Stack<T>& s) {
	stack_node<T>* node = this->head;
	while(node != 0) {
		delete node->data;
		node = node->prev;
	}
	stack_node<T>* next = s.head;
	while(next != 0) {
		push(next->data);
	}
}

template<class T>
void Stack<T>::push(const T& el) {
	stack_node<T>* new_node = new stack_node<T>;
	new_node->prev = this->head;
	new_node->data = new T(el);
	this->head = new_node;
}

template<class T>
void Stack<T>::pop(T& returned) {
	returned = *(head->data);
	delete head->data;
	stack_node<T>* saved = head;
	head = head->prev;
	delete saved;
}

template<class T>
void Stack<T>::peek(T& returned) {
	returned = *(head->data);
}

template<class T>
bool Stack<T>::isEmpty() {
	return head == 0;
}


#endif /* STACK_H_ */
