#pragma once
#include "Structures.h"
#include "LinkedList.h"

template <class T>
struct Stack {
	Stack();
	~Stack();
	T *top;
	void push(T *n);
	T *pop();
	int size;
	bool isEmpty();
};

template <class T>
Stack<T>::Stack() {
	size = 0;
	top = nullptr;
}

template <class T>
Stack<T>::~Stack() {
	while (top != nullptr) {
		T *temp = pop();
		delete temp;
	}
}

template <class T>
void Stack<T>::push(T * n) {
	n->next = top;
	top = n;
	size += 1;
}

template <class T>
T *Stack<T>::pop() {
	if (top != nullptr) {
		T *poppedNode = top;
		top = top->next;
		poppedNode->next = nullptr;
		size -= 1;
		return poppedNode;
	}
	return nullptr;
}

template<class T>
inline bool Stack<T>::isEmpty()
{
	if (size == 0)
		return true;
	return false;
}
