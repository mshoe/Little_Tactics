#pragma once
#include "Classes.h"
#include "Structures.h"
#include "Piece.h"
#include "Tile.h"
#include "Stack.h"
#include "Vector3.h"
#include "Nodes.h"

template <class T>
struct List{
	List();
	~List();
	int size;
	T *start;
	T *getEnd();
	
	bool search(Vector3<int> *coordinates);
	bool search(T *n);
	bool search(Tile *t);
	bool search(Piece *p);
	bool isEmptry();
	void ins(T *n);
	void del();
	T *delNode();
	Piece *delPiece();
	void delSearchPiece(Piece *p);
	T *delSearchTileNode(Tile *t);//takes the node with that tile out of the list
	void delList();
	void printList();
	void printPieces();
	void reverseList();
};

template <class T>
List<T>::List() {
	start = nullptr;
	size = 0;
}

template <class T>
List<T>::~List()
{
	while (start != nullptr) {
		del();
	}
}

template <class T>
T * List<T>::getEnd()
{
	T *temp = start;
	if (temp == nullptr) {
		return temp;
	}
	while (temp->next != nullptr) {
		temp = temp->next;
	}
	return temp;
}

template <class T>
bool List<T>::search(Vector3<int> *coordinates) {
	T *temp = start;
	if (temp == nullptr) {
		return false;
	}
	while (temp->coordinates->x != coordinates->x || temp->coordinates->y != coordinates->y) {
		temp = temp->next;
		if (temp == nullptr)
			return false;
	}
	return true;
}

template <class T>
bool List<T>::search(T *n) {
	T *temp = start;
	if (temp == nullptr) {
		return false;
	}
	while (temp->coordinates->x != n->coordinates->x || temp->coordinates->y != n->coordinates->y) {
		temp = temp->next;
		if (temp == nullptr)
			return false;
	}
	return true;
}

template <class T>
bool List<T>::search(Tile * t)
{
	T *temp = start;
	if (temp == nullptr) {
		return false;
	}
	//just searching for the node coordinatesing to t
	while (temp->tile != t) {
		temp = temp->next;
		if (temp == nullptr)
			return false;
	}
	return true;
}

template <class T>
bool List<T>::search(Piece * p)
{
	T *temp = start;
	if (temp == nullptr) {
		return false;
	}
	//just searching for the node coordinatesing to p
	while (temp->piece != p) {
		temp = temp->next;
		if (temp == nullptr)
			return false;
	}
	return true;
}

template <class T>
bool List<T>::isEmptry() {
	if (start == nullptr) {
		return true;
	}
	return false;
}

template <class T>
void List<T>::ins(T *n) {
	if (start == nullptr) {
		start = n;
	}
	else {
		T *temp = getEnd();
		temp->next = n;
	}
	//might be bugged
	n->next = nullptr;//making sure the last node points to nothing
	size += 1;
}

template <class T>
void List<T>::del() {
	T *temp = start;
	start = start->next;
	//int pos[2]; pos[0] = temp->pos[0]; pos[1] = temp->pos[1];
	delete temp;
	size -= 1;
	return;
}

template <class T>
T * List<T>::delNode()
{
	T *temp = start;
	start = start->next;
	size -= 1;
	return temp;
}

template <class T>
Piece * List<T>::delPiece()
{
	T *temp = start;
	if (start == nullptr)
		return nullptr;
	Piece *piece = start->piece;
	start = start->next;
	delete temp;
	size -= 1;
	return piece;
}

template <class T>
void List<T>::delSearchPiece(Piece * p)
{
	T *temp = start;
	if (temp == nullptr) {
		return;
	}
	else if (temp->piece == p) {
		start = start->next;
		delete temp;
		return;
	}
	else if (temp->next == nullptr) {
		return;
	}
	//just searching for the node coordinatesing to p
	while (temp->next->piece != p) {
		temp = temp->next;
		if (temp->next == nullptr)
			return;
	}
	T *deletedNode = temp->next;
	temp->next = temp->next->next;
	delete deletedNode;
	return;
}

template<class T>
inline T * List<T>::delSearchTileNode(Tile * t)
{
	T *temp = start;
	if (temp == nullptr) {
		return nullptr;
	}
	else if (temp->tile == t) {
		start = start->next;
		return temp;
	}
	else if (temp->next == nullptr) {
		return nullptr;
	}
	//just searching for the node coordinatesing to t
	while (temp->next->tile != t) {
		temp = temp->next;
		if (temp->next == nullptr)
			return nullptr;
	}
	T *deletedNode = temp->next;
	temp->next = temp->next->next;
	return deletedNode;
}

template <class T>
void List<T>::delList() {
	while (start != nullptr) {
		del();
	}
	delete this;
}

template <class T>
void List<T>::printList() {
	Node *temp = start;
	while (temp != nullptr) {
		std::cout << "(" << temp->coordinates->x << "," << temp->coordinates->y << ")  ";
		temp = temp->next;
	}
	std::cout << std::endl;
}

template <class T>
void List<T>::printPieces() {
	T *temp = start;
	while (temp != nullptr) {
		temp->piece->print();
		temp = temp->next;
	}
	std::cout << std::endl;
}

template <class T>
void List<T>::reverseList() {
	Stack<T> *s = new Stack<T>;
	while (start != nullptr) {
		s->push(delNode());
	}
	while (s->top != nullptr) {
		T *temp = s->pop();
		ins(temp);
	}
	delete s;
}
