#pragma once
#include "Classes.h"
#include "Structures.h"

//lower # for priority is better
template <class T>
struct PriorityQueue {
	PriorityQueue();
	~PriorityQueue();
	int size;
	T *front;
	T *rear;
	void enQueue(T *x);
	void insPQueue(PriorityQueue<T> *Q);//deletes the PQ passed into after it is done
	T *deQueue();
	bool searchTile(Tile *t);
	T *getSearchTileNode(Tile *t);
	bool isEmpty();
};

template<class T>
inline PriorityQueue<T>::PriorityQueue()
{
	size = 0;
	front = nullptr;
	rear = nullptr;
}

template<class T>
inline PriorityQueue<T>::~PriorityQueue()
{
	while (!isEmpty()) {
		T * temp = deQueue();
		delete temp;
	}
}

template<class T>
inline void PriorityQueue<T>::enQueue(T * x)
{
	if (x == nullptr) {
		return;
	}
	if (size == 0) {
		front = x;
		rear = x;
		x->next = nullptr;//being safe
		size = 1;
	}
	else if (size == 1) {
		if (x->fScore > rear->fScore) {
			rear->next = x;
			rear = x;
			x->next = nullptr;//staying safe
			size += 1;
		}
		else {
			x->next = front;
			front = x;
			size += 1;
		}
	}
	else {
		T *temp = front;
		while (x->fScore > temp->next->fScore) {
			if (temp->next == rear) {
				rear->next = x;
				rear = x;
				x->next = nullptr;
				size += 1;
				return;
			}
			temp = temp->next;
		}
		x->next = temp->next;
		temp->next = x;
		size += 1;
	}
}

template<class T>
inline void PriorityQueue<T>::insPQueue(PriorityQueue<T>* Q)
{
	while (!Q->isEmpty()) {
		T *temp = Q->deQueue();
		this->enQueue(temp);
	}
	delete Q;
}

template<class T>
inline T * PriorityQueue<T>::deQueue()
{
	T *temp = front;
	front = front->next;
	size -= 1;
	return temp;
}

template<class T>
inline bool PriorityQueue<T>::searchTile(Tile * t)
{
	T *temp = front;
	while (temp != nullptr) {
		if (temp->tile == t) {
			return true;
		}
		temp = temp->next;
	}
	return false;
}

template<class T>
inline T * PriorityQueue<T>::getSearchTileNode(Tile * t)
{
	T *temp = front;
	while (temp != nullptr) {
		if (temp->tile == t) {
			return temp;
		}
		temp = temp->next;
	}
	return nullptr;
}

template<class T>
inline bool PriorityQueue<T>::isEmpty()
{
	if (size == 0)
		return true;
	return false;
}
