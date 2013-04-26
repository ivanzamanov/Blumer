/*
 * queue.h
 *
 *  Created on: Apr 26, 2013
 *      Author: ivo
 */

#ifndef queue_H_
#define queue_H_

template<class T>
class Queue {
public:
	Queue<T>();
	Queue<T>(const Queue& s);
	const Queue<T>& operator=(const Queue<T>& s);
	virtual ~Queue<T>();

	virtual void push(const T& el);
	virtual void pop(T& returned);
	virtual T& peek();
	virtual T& peek_last();
	virtual bool isEmpty();

private:
	template<class V>
	struct queue_node {
		V* data = 0;
		queue_node* next = 0;
	};
	queue_node<T>* head = 0;
	queue_node<T>* tail = 0;
};


template<class T>
Queue<T>::Queue() {

}

template<class T>
Queue<T>::Queue(const Queue<T>& s) {
	queue_node<T>* next = s.head;
	while(next != 0) {
		push(*(next->data));
	}
}

template<class T>
Queue<T>::~Queue() {
	queue_node<T>* node = this->head;
	while(node != 0) {
		delete node->data;
		node = node->next;
	}
}

template<class T>
const Queue<T>& Queue<T>::operator =(const Queue<T>& s) {
	queue_node<T>* node = this->head;
	while(node != 0) {
		delete node->data;
		node = node->next;
	}
	tail = 0;
	queue_node<T>* next = s.head;
	while(next != 0) {
		push(*(next->data));
	}
	return *this;
}

template<class T>
void Queue<T>::push(const T& el) {
	queue_node<T>* new_node = new queue_node<T>;
	if(head == 0) {
		head = new_node;
	}
	if(tail != 0) {
		tail->next = new_node;
	}
	new_node->data = new T(el);
	this->tail = new_node;
}

template<class T>
void Queue<T>::pop(T& returned) {
	returned = *(head->data);
	delete head->data;
	queue_node<T>* saved = head;
	if(head == tail)
		tail = 0;
	head = head->next;
	delete saved;
}

template<class T>
T& Queue<T>::peek() {
	return *(head->data);
}

template<class T>
T& Queue<T>::peek_last() {
	return *(tail->data);
}

template<class T>
bool Queue<T>::isEmpty() {
	return head == 0;
}

#endif /* queue_H_ */
