#include "Nodes.h"

Node::Node() {
	//pos[0] = 0; pos[1] = 1;
	next = nullptr;
	piece = nullptr;
	tile = nullptr;
	MOV = 0;
	//priority = 0;
	coordinates = new Vector3<int>;
}

Node::Node(int x, int y) {
	//pos[0] = x; pos[1] = y;
	next = nullptr;
	piece = nullptr;
	tile = nullptr;
	MOV = 0;
	//priority = 0;
	coordinates = new Vector3<int>(x, y);
}

Node::Node(Tile *tile) {
	if (tile != nullptr) {
		next = nullptr;
		piece = nullptr;
		this->tile = tile;
		MOV = 0;
		//priority = 0;
		coordinates = new Vector3<int>(tile->coordinates->x, tile->coordinates->y);
	}
	else {
		next = nullptr;
		piece = nullptr;
		this->tile = nullptr;
		MOV = 0;
		//priority = 0;
		coordinates = nullptr;
	}
}

Node::Node(Tile * tile, int MOV, int priority)
{
	if (tile != nullptr) {
		//this->pos[0] = tile->getPos()[0]; this->pos[1] = tile->getPos()[1];
		next = nullptr;
		piece = nullptr;
		this->tile = tile;
		this->MOV = MOV;
		//this->priority = priority;
		coordinates = new Vector3<int>(tile->coordinates->x, tile->coordinates->y);
	}
	else {//To make the movList algorithm easier
		this->tile = nullptr;
	}
}

Node::Node(Tile *tile, int MOV) {
	if (tile != nullptr) {
		//this->pos[0] = tile->getPos()[0]; this->pos[1] = tile->getPos()[1];
		next = nullptr;
		piece = nullptr;
		this->tile = tile;
		this->MOV = MOV;
		//priority = 0;
		coordinates = new Vector3<int>(tile->coordinates->x, tile->coordinates->y);
	}
	else {//To make the movList algorithm easier
		this->tile = nullptr;
		//priority = 0;
	}
}

Node::Node(Piece *piece) {
	//pos[0] = piece->pos[0]; pos[1] = piece->pos[1];
	next = nullptr;
	this->piece = piece;
	tile = piece->getTile();
	coordinates = new Vector3<int>(piece->coordinates->x, piece->coordinates->y);
	MOV = 0;
	//priority = 0;
}

Node::~Node()
{
	delete coordinates;
}

MovementNode::MovementNode()
{
	piece = nullptr;
	tile = nullptr;
	next = nullptr;
	MOV = 1;
	gScore = 1;
	fScore = 1;
}

MovementNode::MovementNode(Piece * piece, Tile * tile)
{
	this->piece = piece;
	this->tile = tile;
	next = nullptr;
	cameFrom = nullptr;
	MOV = 1;
	gScore = 1;
	fScore = 1;
}

MovementNode::MovementNode(Piece * piece, Tile * tile, int gScore, int fScore)
{
	this->piece = piece;
	this->tile = tile;
	next = nullptr;
	cameFrom = nullptr;
	MOV = 1;
	this->gScore = gScore;
	this->fScore = fScore;
}

MovementNode::~MovementNode()
{
}

AttackNode::AttackNode()
{
	piece1 = nullptr;
	piece2 = nullptr;
	tile = piece1->getTile();
	next = nullptr;
	MOV = 1;
	gScore = 1;
	fScore = 1;
}

AttackNode::AttackNode(int ATK, Piece * piece1, Piece * piece2)
{
	this->piece1 = piece1;
	this->piece2 = piece2;
	tile = piece1->getTile();
	next = nullptr;
	MOV = 1;
	this->ATK = ATK;
	p1Coords = new Vector3<float>(piece1->coordinates->x, piece1->coordinates->y, piece1->coordinates->z);
	gScore = 1;
	fScore = 1;
}

AttackNode::AttackNode(int ATK, Piece * piece1, Piece * piece2, int fScore)
{
	this->piece1 = piece1;
	this->piece2 = piece2;
	tile = piece1->getTile();
	next = nullptr;
	MOV = 1;
	this->ATK = ATK;
	p1Coords = new Vector3<float>(piece1->coordinates->x, piece1->coordinates->y, piece1->coordinates->z);
	gScore = 1;
	this->fScore = fScore;
}

AttackNode::~AttackNode()
{
	if (p1Coords != nullptr)
		delete p1Coords;
}
