#include "Piece.h"
#include <iostream>

Piece::Piece() {
	character = 32;
	stats = new Stats;
	tile = nullptr;
	type = 0;

	//Physical Properties
	size = 0.5f;
	fullSize = 0.5f;
	color = new Vector3<float>;
	coordinates = new Vector3<float>;

	int i;
	for (i = 0; i < 24; i++) {
		vertices[i] = new Vector3<float>;
	}
	//updateVertices();
}

Piece::Piece(char x) {
	character = x;
	stats = new Stats;
	type = 0;
	tile = nullptr;

	//Physical Properties
	size = 0.5f;
	fullSize = 0.5f;
	color = new Vector3<float>;
	coordinates = new Vector3<float>;

	int i;
	for (i = 0; i < 24; i++) {
		vertices[i] = new Vector3<float>;
	}
	//updateVertices();
}

Piece::Piece(char x, int hp, int atk, int spd, int mov, int jmp, int type) {
	character = x;
	stats = new Stats(hp, atk, spd, mov, jmp);
	this->type = type;
	tile = nullptr;

	//Physical Properties
	size = 0.5f;
	fullSize = 0.5f;
	color = new Vector3<float>;
	coordinates = new Vector3<float>;
	
	int i;
	for (i = 0; i < 24; i++) {
		vertices[i] = new Vector3<float>;
	}
	//updateVertices();
}

Piece::Piece(char x, int hp, int atk, int spd, int mov, int jmp, int type, float xColor, float yColor, float zColor) {
	character = x;
	stats = new Stats(hp, atk, spd, mov, jmp);
	this->type = type;
	tile = nullptr;

	//Physical Properties
	if (type == 0)//initial facing conditions
		facing = SOUTH;
	else
		facing = NORTH;
	tileSize = 0.75f;
	size = 0.5f;
	fullSize = 0.5f;
	color = new Vector3<float>(xColor, yColor, zColor);
	coordinates = new Vector3<float>;

	int i;
	for (i = 0; i < 24; i++) {
		vertices[i] = new Vector3<float>;
	}
	//updateVertices();
}

Piece::~Piece()
{
	delete stats;
	delete coordinates;
	delete color;
	int i;
	for (i = 0; i < 24; i++) {
		delete vertices[i];
	}
}

char Piece::getChar() {
	return character;
}

void Piece::updateVertices()
{
	//Call this function every time the coordinates are changed
	float x = coordinates->x; float y = coordinates->y; float z = coordinates->z;
	//float tileSize = tile->size;

	//Pieces will be more flat than tiles

	//TOP
	vertices[0]->changeVector(x + size / 2, y + size / 2, z + tileSize / 2 + size / 2);
	vertices[1]->changeVector(x - size / 2, y + size / 2, z + tileSize / 2 + size / 2);
	vertices[2]->changeVector(x - size / 2, y - size / 2, z + tileSize / 2 + size / 2);
	vertices[3]->changeVector(x + size / 2, y - size / 2, z + tileSize / 2 + size / 2);

	//BOTTOM
	vertices[4]->changeVector(x + size / 2, y - size / 2, z + tileSize / 2);
	vertices[5]->changeVector(x - size / 2, y - size / 2, z + tileSize / 2);
	vertices[6]->changeVector(x - size / 2, y + size / 2, z + tileSize / 2); 
	vertices[7]->changeVector(x + size / 2, y + size / 2, z + tileSize / 2); 

	//EAST
	vertices[8]->changeVector(x + size / 2, y + size / 2, z + tileSize / 2 + size / 2);
	vertices[9]->changeVector(x - size / 2, y + size / 2, z + tileSize / 2 + size / 2);
	vertices[10]->changeVector(x - size / 2, y + size / 2, z + tileSize / 2);
	vertices[11]->changeVector(x + size / 2, y + size / 2, z + tileSize / 2);

	//WEST
	vertices[12]->changeVector(x + size / 2, y - size / 2, z + tileSize / 2 + size / 2);
	vertices[13]->changeVector(x - size / 2, y - size / 2, z + tileSize / 2 + size / 2);
	vertices[14]->changeVector(x - size / 2, y - size / 2, z + tileSize / 2);
	vertices[15]->changeVector(x + size / 2, y - size / 2, z + tileSize / 2);

	//NORTH
	vertices[16]->changeVector(x + size / 2, y + size / 2, z + tileSize / 2 + size / 2);
	vertices[17]->changeVector(x + size / 2, y - size / 2, z + tileSize / 2 + size / 2);
	vertices[18]->changeVector(x + size / 2, y - size / 2, z + tileSize / 2);
	vertices[19]->changeVector(x + size / 2, y + size / 2, z + tileSize / 2);

	//SOUTH
	vertices[20]->changeVector(x - size / 2, y + size / 2, z + tileSize / 2 + size / 2);
	vertices[21]->changeVector(x - size / 2, y - size / 2, z + tileSize / 2 + size / 2);
	vertices[22]->changeVector(x - size / 2, y - size / 2, z + tileSize / 2);
	vertices[23]->changeVector(x - size / 2, y + size / 2, z + tileSize / 2);
}

void Piece::changeChar(char x) {
	character = x;
}

void Piece::print()
{
	std::cout << "[ (" << coordinates->x << "," << coordinates->y << ") HP: " << stats->HP << ", ATK: " << stats->ATK << ", MOV: " << stats->MOV << " ] ";
}

void Piece::printCoordinates()
{
	std::cout << "(" << coordinates->x << "," << coordinates->y << ") ";
}

Tile * Piece::getTile()
{
	return tile;
}

float Piece::getFullSize()
{
	return fullSize;
}

void Piece::changeTile(Tile *tile) {
	this->tile = tile;
}