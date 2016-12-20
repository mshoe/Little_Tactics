#include "Tile.h"
#include "GameBoard.h"
#include <iostream>

Tile::Tile() {
	piece = nullptr;
	North = nullptr;
	South = nullptr;
	East = nullptr;
	West = nullptr;
	Up = nullptr;
	Down = nullptr;
	
	//Physical Properties
	size = 0.75f;
	color = new Vector3<float>;
	coordinates = new Vector3<float>;

	int i;
	for (i = 0; i < 24; i++) {
		vertices[i] = new Vector3<float>;
	}
	updateVertices();
}

Tile::Tile(float x, float y) {
	piece = nullptr;
	North = nullptr;
	South = nullptr;
	East = nullptr;
	West = nullptr;
	Up = nullptr;
	Down = nullptr;

	//Physical Properties
	size = 0.75f;
	color = new Vector3<float>;
	coordinates = new Vector3<float>(x, y);

	int i;
	for (i = 0; i < 24; i++) {
		vertices[i] = new Vector3<float>;
	}
	updateVertices();
}

Tile::Tile(float x, float y, float z) {
	piece = nullptr;
	North = nullptr;
	South = nullptr;
	East = nullptr;
	West = nullptr;
	Up = nullptr;
	Down = nullptr;

	//Physical Properties
	size = 0.75f;
	color = new Vector3<float>;
	coordinates = new Vector3<float>(x, y, z);

	int i;
	for (i = 0; i < 24; i++) {
		vertices[i] = new Vector3<float>;
	}
	updateVertices();
}

Tile::Tile(float x, float y, float z, float xColor, float yColor, float zColor)
{
	piece = nullptr;
	North = nullptr;
	South = nullptr;
	East = nullptr;
	West = nullptr;
	Up = nullptr;
	Down = nullptr;

	//Physical Properties
	size = 0.75f;
	color = new Vector3<float>(xColor, yColor, zColor);
	coordinates = new Vector3<float>(x, y, z);

	int i;
	for (i = 0; i < 24; i++) {
		vertices[i] = new Vector3<float>;
	}
	updateVertices();
}

Tile::~Tile()
{
	delete coordinates;
	delete color;
	int i;
	for (i = 0; i < 24; i++) {
		delete vertices[i];
	}
}

Piece *Tile::getPiece() {
	return piece;
}

void Tile::changePiece(Piece *x) {
	piece = x;
	if (x != nullptr) {
		piece->changeTile(this);
		piece->coordinates->changeVector(this->coordinates->x, this->coordinates->y, this->coordinates->z);
		piece->updateVertices();
	}
}

void Tile::updateVertices()
{
	//Call this function every time the coordinates are changed
	float x = (float)coordinates->x; float y = (float)coordinates->y; float z = (float)coordinates->z;
	//TOP
	vertices[0]->changeVector(x + size / 2, y + size / 2, z + size / 2);
	vertices[1]->changeVector(x - size / 2, y + size / 2, z + size / 2);
	vertices[2]->changeVector(x - size / 2, y - size / 2, z + size / 2);
	vertices[3]->changeVector(x + size / 2, y - size / 2, z + size / 2);

	//BOTTOM
	vertices[4]->changeVector(x + size / 2, y - size / 2, z - size / 2);
	vertices[5]->changeVector(x - size / 2, y - size / 2, z - size / 2); 
	vertices[6]->changeVector(x - size / 2, y + size / 2, z - size / 2);
	vertices[7]->changeVector(x + size / 2, y + size / 2, z - size / 2); 

	//EAST
	vertices[8]->changeVector(x + size / 2, y + size / 2, z + size / 2);
	vertices[9]->changeVector(x - size / 2, y + size / 2, z + size / 2);
	vertices[10]->changeVector(x - size / 2, y + size / 2, z - size / 2);
	vertices[11]->changeVector(x + size / 2, y + size / 2, z - size / 2);

	//WEST
	vertices[12]->changeVector(x + size / 2, y - size / 2, z + size / 2);
	vertices[13]->changeVector(x - size / 2, y - size / 2, z + size / 2);
	vertices[14]->changeVector(x - size / 2, y - size / 2, z - size / 2);
	vertices[15]->changeVector(x + size / 2, y - size / 2, z - size / 2);

	//NORTH
	vertices[16]->changeVector(x + size / 2, y + size / 2, z + size / 2);
	vertices[17]->changeVector(x + size / 2, y - size / 2, z + size / 2);
	vertices[18]->changeVector(x + size / 2, y - size / 2, z - size / 2);
	vertices[19]->changeVector(x + size / 2, y + size / 2, z - size / 2);

	//SOUTH
	vertices[20]->changeVector(x - size / 2, y + size / 2, z + size / 2);
	vertices[21]->changeVector(x - size / 2, y - size / 2, z + size / 2);
	vertices[22]->changeVector(x - size / 2, y - size / 2, z - size / 2);
	vertices[23]->changeVector(x - size / 2, y + size / 2, z - size / 2);
}

void Tile::linkTileNorth(Tile *tile) {
	North = tile;
}

void Tile::linkTileSouth(Tile * tile) {
	South = tile;
}

void Tile::linkTileWest(Tile * tile) {
	West = tile;
}

void Tile::linkTileEast(Tile * tile) {
	East = tile;
}

void Tile::linkTileUp(Tile * tile) {
	Up = tile;
}

void Tile::linkTileDown(Tile * tile) {
	Down = tile;
}

Tile * Tile::getTileNorth()
{
	return North;
}

Tile * Tile::getTileSouth()
{
	return South;
}

Tile * Tile::getTileWest()
{
	return West;
}

Tile * Tile::getTileEast()
{
	return East;
}

Tile * Tile::getTileUp()
{
	return Up;
}

Tile * Tile::getTileDown()
{
	return Down;
}

Tile * Tile::getTileDirection(int direction)
{
	if (direction == NORTH)
		return getTileNorth();
	if (direction == EAST)
		return getTileEast();
	if (direction == SOUTH)
		return getTileSouth();
	if (direction == WEST)
		return getTileWest();
	if (direction == UP)
		return getTileUp();
	if (direction == DOWN)
		return getTileDown();
	return nullptr;
}
