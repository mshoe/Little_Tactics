#pragma once
#include "Structures.h"
#include "LinkedList.h"

//PRIORITY QUEUE

template <class T>
struct Queue {//This will be used for breadth-first traversal of movement
	Queue();
	~Queue();
	int size;
	T *front;
	T *rear;
	void enQueue(T *x);
	void insQueue(Queue<T> *Q);
	bool isEmpty();
	T *deQueue();
};

template <class T>
Queue<T>::Queue() {
	front = nullptr;
	rear = nullptr;
	size = 0;
}

template<class T>
Queue<T>::~Queue()
{
	while (size != 0) {
		T *temp = deQueue();
		delete temp;
	}
}

template <class T>
void Queue<T>::enQueue(T *x) {
	if (x == nullptr) {
		return;
	}
	else if (x->tile == nullptr) {//makes algorithm easier
		return;
	}
	else if (x->MOV == 0) {//one of base cases
		return;
	}
	if (size == 0) {
		front = x;
		rear = x;
		size = 1;
	}
	else {
		rear->next = x;
		rear = x;
		size += 1;
	}
}

template<class T>
inline void Queue<T>::insQueue(Queue<T> * Q)
{
	while (!Q->isEmpty()) {
		T *temp = Q->deQueue();
		this->enQueue(temp);
	}
	delete Q;
}

template<class T>
inline bool Queue<T>::isEmpty()
{
	if (size == 0)
		return true;
	return false;
}

template <class T>
T *Queue<T>::deQueue() {
	T *temp = front;
	front = front->next;
	size -= 1;
	return temp;
}