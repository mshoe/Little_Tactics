#pragma once
#include "Classes.h"
#include "Structures.h"
#include "Piece.h"
#include "Tile.h"
#include "Stack.h"
#include "Vector3.h"

struct Node {
	Node();
	Node(int, int);
	Node(Tile *tile);
	Node(Tile *tile, int MOV, int priority);
	Node(Tile *tile, int MOV);
	Node(Piece *piece);
	~Node();
	Piece *piece;//not deleting this in del(), because that would remove piece from board
	Tile *tile;
	Vector3<int> *coordinates;
	Node *next;
	//int priority;
	int MOV;//this is for making the move list, helps with recursion
};

struct MovementNode {
	MovementNode();
	MovementNode(Piece *piece, Tile *tile);
	MovementNode(Piece *piece, Tile *tile, int gScore, int fScore);
	~MovementNode();
	Piece *piece;
	Tile *tile;
	MovementNode *next;
	MovementNode *cameFrom;
	int MOV;//useless but needed for existing enQueue code
	int gScore;
	int fScore;
};

struct AttackNode {
	AttackNode();
	AttackNode(int ATK, Piece *piece1, Piece *piece2);
	AttackNode(int ATK, Piece *piece1, Piece *piece2, int fScore);
	~AttackNode();
	Piece *piece1;
	Vector3<float> *p1Coords;
	Piece *piece2;
	Tile *tile;//useless but needed for existing enQueue code
	AttackNode *next;
	int MOV;//useless but needed for existing enQueue code
	int ATK;
	int gScore;
	int fScore;
};