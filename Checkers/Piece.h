#pragma once
#include "Classes.h"
#include "Stats.h"
#include "Tile.h"
#include "Vector3.h"
//Stats should normally be 2 hp, 2 mov, 1 atk

class Piece {
public:
	Piece();
	Piece(char x);
	Piece(char x, int hp, int atk, int spd, int mov, int jmp, int type);
	Piece(char x, int hp, int atk, int spd, int mov, int jmp, int type, float xColor, float yColor, float zColor);
	~Piece();
	char getChar();
	void updateVertices();
	void changeChar(char x);
	void print();
	void printCoordinates();
	void changeTile(Tile *tile);
	Tile *getTile();

	//Properties
	int type;// can enum 1 for player, 0 for enemy
	Stats *stats;

	//Physical Properties
	float size;
	float getFullSize();
	Vector3<float> *color;
	Vector3<float> *coordinates;
	Vector3<float> *vertices[24];
	int facing;//where the qt3.14 eyes are
	float tileSize;

private:
	float fullSize;
	Tile *tile;
	char character;
};

enum direction {
	NORTH = 1,
	EAST = 2,
	SOUTH = 3,
	WEST = 4,
	UP = 5,
	DOWN = 6
};