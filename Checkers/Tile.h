#pragma once
#include "Classes.h"
#include "Piece.h"
#include "Vector3.h"

class Tile {
public:
	Tile();
	Tile(float, float);
	Tile(float, float, float);
	Tile(float, float, float, float xColor, float yColor, float zColor);
	~Tile();
	Piece *getPiece();
	void changePiece(Piece *x);
	void updateVertices();
	//Not doing a general link tile here, because can't access gameBoard
	void linkTileNorth(Tile *tile);//can only be used after all tiles are made
	void linkTileSouth(Tile *tile);
	void linkTileWest(Tile *tile);
	void linkTileEast(Tile *tile);
	void linkTileUp(Tile *tile);
	void linkTileDown(Tile *tile);
	Tile *getTileNorth();
	Tile *getTileSouth();
	Tile *getTileWest();
	Tile *getTileEast();
	Tile *getTileUp();
	Tile *getTileDown();
	Tile *getTileDirection(int);

	//Render and Physics Properties
	float size;//0.75f default
	Vector3<float> *color;
	Vector3<float> *coordinates;
	Vector3<float> *vertices[24];

private:
	Tile *North;
	Tile *South;
	Tile *West;
	Tile *East;
	Tile *Up;
	Tile *Down;
	Piece *piece;
};