#pragma once
#include "Classes.h"
#include "Tile.h"
#include "LinkedList.h"
#include "Vector3.h"

class GameBoard {
public:
	GameBoard();
	GameBoard(int, int, int);
	//int * getPosition(int x, int y);
	void initBoard(int, int, int);
	/*void printBoard();
	void printBoard(List *movList);
	void printBoard(List *atkList, int z);*/
	void linkTiles(int rows, int cols, int height);
	void updateAdjMatrix();

	int ROWS; int COLS; int HEIGHT;
	Tile**** getBoard();
	Tile* getTile(Vector3<float> *coordinates);
private:
	Tile**** board;//ptr to a 3D array of Tile ptrs
	//adjMatrix *adjMat;
};