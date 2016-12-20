#include "PlayerGame.h"
#include <iostream>
#include <string>

#include <typeinfo>

PlayerGame::PlayerGame() {
	Init();
}

//INHERITED MEMBERS OF CGameState CLASS

void PlayerGame::Init()
{
	//order matters
	gameBoard = new GameBoard(8, 8, 1);

	ui = new UIBackend(this);
	ui->turn = 1;
	ui->firstAction = 0;
	ui->secondAction = 0;
	ui->actionSelection = MOVE;
	ui->leftRightSelection = RIGHT;
	ui->currentAction = 0;

	renderer = new Renderer(this);
	//not anymore

	winner = -1;
	/*isAnimatingMovement = false;
	isAnimatingAttack = false;*/

	keyIn = new KeyInput(this);

	currentMovementList = nullptr;
	currentAttackList = nullptr;
	currentPiece = nullptr;
	piece1 = nullptr;
	piece2 = nullptr;
	pieceState = PIECE_INACTIVE;
	currentTile = nullptr;
	selector = new Vector3<float>;
	selectorState = SELECTOR_INACTIVE;

	/*movementQueue = new Queue<MovementNode>;
	movementStack = new Stack<MovementNode>;
	attackQueue = new PriorityQueue<AttackNode>;*/

	playerPieceList = makePieceList(1);
	cpuPieceList = makePieceList(0);

	ai = new AI(this);

	anim = new Animation(this);

	renderer->setAnim(anim);
	keyIn->setAnim(anim);

	elapsedTime = 0;
}

void PlayerGame::CleanUp()
{
	delete gameBoard;
	delete selector;
	delete renderer;
	delete keyIn;
	delete ui;
	/*delete movementStack;
	delete movementQueue;*/
}

void PlayerGame::Pause()
{
}

void PlayerGame::Resume()
{
}

void PlayerGame::KeyBoard(unsigned char key, int x, int y, CGameEngine * gameEngine)
{
	auto t1 = Clock::now();
	keyIn->KeyBoard(key, x, y, gameEngine);
	auto t2 = Clock::now();
	elapsedTime += std::chrono::duration<double>(t2 - t1).count();
}



void PlayerGame::IdleUpdate(CGameEngine * gameEngine)
{
	auto t1 = Clock::now();
	winner = checkWinner();
	if (!anim->isMovementQueueEmpty()) {
		keyIn->keyBoardActive = false;
		anim->animateMovementQueue();
		if (anim->isMovementQueueEmpty() && piece1 != nullptr && piece2 != nullptr) {
			attackPieceChainQ(piece1, piece2);
			piece1 = nullptr; piece2 = nullptr;
		}
	}
	else if (!anim->isAttackQueueEmpty()) {
		keyIn->keyBoardActive = false;
		anim->animateAttackQueue();
	}
	else {
		keyIn->keyBoardActive = true;
	}
	glutPostRedisplay();
	auto t2 = Clock::now();
	elapsedTime = std::chrono::duration<double>(t2 - t1).count();
}

void PlayerGame::Draw(CGameEngine * gameEngine)
{
	auto t1 = Clock::now();
	renderer->renderGame();
	auto t2 = Clock::now();
	elapsedTime += std::chrono::duration<double>(t2 - t1).count();
}

//FUNDAMENTAL ACTIONS
void PlayerGame::movePiece(Piece *piece, Tile *tile) {
	/*Tile *tile2 = piece->getTile();
	tile2->changePiece(nullptr);*/
	anim->movementQueue->enQueue(new MovementNode(piece, tile));
	//tile->changePiece(piece);
	updateStats();
}

void PlayerGame::attackPiece(int ATK, Piece *piece1, Piece *piece2) {
	anim->attackQueue->enQueue(new AttackNode(ATK, piece1, piece2));
	//piece2->stats->HP -= piece1->stats->ATK;
	//char piece2Char = piece2->getChar();
	//char piece2newChar = 96;
	//if (piece2Char == 88)
	//	piece2newChar = 120;
	//else if (piece2Char == 79)
	//	piece2newChar = 111;
	//if (piece2->stats->HP == 1) {
	//	piece2->changeChar(piece2newChar);
	//	piece2->size /= 2;
	//	piece2->updateVertices();
	//}
	////else if kill
	//else if (piece2->stats->HP <= 0) {
	//	piece2->getTile()->changePiece(nullptr);
	//	delPiece(piece2);
	//}
	//updateStats();
}

void PlayerGame::delPiece(Piece *piece) {
	Tile *tile = gameBoard->getTile(piece->coordinates);
	tile->changePiece(nullptr);
	playerPieceList->delSearchPiece(piece);
	cpuPieceList->delSearchPiece(piece);
	delete piece;
}

void PlayerGame::updateStats() {
	List<Node> *pieceList0 = makePieceList(0);
	List<Node> *pieceList1 = makePieceList(1);
	updatePieceListStats(pieceList0);
	updatePieceListStats(pieceList1);
	pieceList0->delList(); pieceList1->delList();
}

void PlayerGame::updatePieceListStats(List<Node> *pieceList) {
	Node *temp = pieceList->start;
	Piece *piece;
	while (temp != nullptr) {
		piece = temp->piece;
		List<Node> *chainList = makeChainList(piece);
		if (chainList->size == 1) {
			piece->stats->ATK = 1;
			piece->stats->MOV = 2;
		}
		else if (chainList->size == 2) {
			piece->stats->ATK = 1;
			piece->stats->MOV = 3;
		}
		else if (chainList->size == 3) {
			piece->stats->ATK = 2;
			piece->stats->MOV = 3;
		}
		else if (chainList->size >= 4) {
			piece->stats->ATK = 2;
			piece->stats->MOV = chainList->size;
		}
		chainList->delList();
		temp = temp->next;
	}
}

void PlayerGame::nextTurn()
{
	ui->turn += 1;
	ui->firstAction = 0;
	ui->secondAction = 0;
	ui->actionSelection = MOVE;
	ui->currentAction = 0;

	currentMovementList = nullptr;
	currentAttackList = nullptr;
	currentPiece = nullptr;
	currentTile = nullptr;
}

void PlayerGame::restart()
{
	CleanUp();
	Init();
}

//MISC. TOOLS

int PlayerGame::checkWinner() {
	if (playerPieceList->start == nullptr) {
		//std::cout << "O Wins." << std::endl;
		return 0;
	}
	else if (cpuPieceList->start == nullptr) {
		//std::cout << "X Wins." << std::endl;
		return 1;
	}
	else {
		return -1;
	}
}

int PlayerGame::getType() {
	//returning the type (player or enemy) who gets to go this turn
	if (ui->turn % 2 == 0)
		return 0;
	else
		return 1;
}

int PlayerGame::getOppType() {
	if (ui->turn % 2 == 0)
		return 1;
	else
		return 0;
}

Tile *PlayerGame::selectTile(Vector3<float> *coordinates) {
	Tile**** board = gameBoard->getBoard();
	return board[(int)coordinates->z][(int)coordinates->x][(int)coordinates->y];
}

bool PlayerGame::correctTurn(Piece *piece) {
	if (piece != nullptr) {
		if (ui->turn % 2 == 0) {
			if (piece->type == 1)
				return false;
			else if (piece->type == 0)
				return true;
		}
		else {
			if (piece->type == 1)
				return true;
			if (piece->type == 0)
				return false;
		}
	}
	return false;
}

bool PlayerGame::availableMoves()
{
	List<Node> *pieceList = makePieceList(getType());
	List<Node> *availableMovList = makeAvailableMovList(pieceList);
	if (availableMovList->start == nullptr) {
		std::cout << "No available moves." << std::endl;
		availableMovList->delList();
		pieceList->delList();
		return false;
	}
	else {
		availableMovList->delList();
		pieceList->delList();
		return true;
	}
}

bool PlayerGame::availableAttacks()
{
	List<Node> *pieceList = makePieceList(getType());
	List<Node> *availableAtkList = makeAvailableAtkList(pieceList);
	if (availableAtkList->start == nullptr) {
		std::cout << "No available attacks." << std::endl;
		availableAtkList->delList();
		pieceList->delList();
		return false;
	}
	else {
		availableAtkList->delList();
		pieceList->delList();
		return true;
	}
}

//BASIC PIECE LISTS

List<Node> *PlayerGame::makeMovList(Piece *piece) {
	//Use of queues for Breadth-First Traversal
	List<Node> *movList = new List<Node>;
	Tile *tile = piece->getTile();
	int MOV = piece->stats->MOV;
	int movTemp = 0;
	Queue<Node> *Q = new Queue<Node>;
	//no need to movList->ins(new Node(tile)); because algorithm will check for tiles with pieces
	Q->enQueue(new Node(tile->getTileNorth(), MOV));
	Q->enQueue(new Node(tile->getTileSouth(), MOV));
	Q->enQueue(new Node(tile->getTileWest(), MOV));
	Q->enQueue(new Node(tile->getTileEast(), MOV));
	while (Q->size != 0) {
		Node *temp = Q->deQueue();
		tile = temp->tile;
		movTemp = temp->MOV;
		if (tile->getPiece() == nullptr) {
			if (!movList->search(tile)) {
				movList->ins(new Node(tile));
				Q->enQueue(new Node(tile->getTileNorth(), movTemp - 1));
				Q->enQueue(new Node(tile->getTileSouth(), movTemp - 1));
				Q->enQueue(new Node(tile->getTileWest(), movTemp - 1));
				Q->enQueue(new Node(tile->getTileEast(), movTemp - 1));
			}
		}
	}
	delete Q;
	return movList;
}

List<Node> *PlayerGame::makeAjcAllyList(Piece *piece) {
	//Make adjacent ally list
	List<Node> *ajcList = new List<Node>;
	Tile *tile2;
	Tile *pieceTile = piece->getTile();
	int pieceType = piece->type;
	tile2 = pieceTile->getTileNorth();
	addPieceAjcList(tile2, ajcList, pieceType);
	tile2 = pieceTile->getTileSouth();
	addPieceAjcList(tile2, ajcList, pieceType);
	tile2 = pieceTile->getTileWest();
	addPieceAjcList(tile2, ajcList, pieceType);
	tile2 = pieceTile->getTileEast();
	addPieceAjcList(tile2, ajcList, pieceType);
	return ajcList;
}

void PlayerGame::addPieceAjcList(Tile * tile, List<Node> * ajcList, int type)
{
	Piece *piece;
	if (tile != nullptr) {
		piece = tile->getPiece();
		if (piece != nullptr) {
			if (piece->type == type) {
				ajcList->ins(new Node(piece));
			}
		}
	}
}

List<Node> *PlayerGame::makeAtkList(Piece *piece) {
	int x = piece->coordinates->x;
	int y = piece->coordinates->y;
	List<Node> *atkList = new List<Node>;
	int pieceType = piece->type;
	Tile *pieceTile;
	Piece *pieceAttack;
	pieceTile = piece->getTile();
	//could make this smaller
	if (x != 0) {
		pieceAttack = pieceTile->getTileNorth()->getPiece();
		if (pieceAttack != nullptr) {
			if (pieceAttack->type != pieceType)
				atkList->ins(new Node(pieceAttack));
		}
	}
	if (x != gameBoard->ROWS - 1) {
		pieceAttack = pieceTile->getTileSouth()->getPiece();
		if (pieceAttack != nullptr) {
			if (pieceAttack->type != pieceType)
				atkList->ins(new Node(pieceAttack));
		}
	}
	if (y != 0) {
		pieceAttack = pieceTile->getTileWest()->getPiece();
		if (pieceAttack != nullptr) {
			if (pieceAttack->type != pieceType)
				atkList->ins(new Node(pieceAttack));
		}
	}
	if (y != gameBoard->COLS - 1) {
		pieceAttack = pieceTile->getTileEast()->getPiece();
		if (pieceAttack != nullptr) {
			if (pieceAttack->type != pieceType)
				atkList->ins(new Node(pieceAttack));
		}
	}
	return atkList;
}

List<Node> *PlayerGame::makePieceList(int type) {
	List<Node> *pieceList = new List<Node>;
	Piece *piece;
	int i, j;
	int selection = 0;
	//making the lists
	for (i = 0; i < gameBoard->ROWS; i++) {
		for (j = 0; j < gameBoard->COLS; j++) {
			Vector3<float> *coordinates = new Vector3<float>(i, j);
			if (gameBoard->getTile(coordinates)->getPiece() != nullptr) {
				piece = gameBoard->getTile(coordinates)->getPiece();
				if (piece->type == type)
					pieceList->ins(new Node(piece));
			}
			delete coordinates;
		}
	}
	return pieceList;
}

List<Node> *PlayerGame::makeAvailableMovList(List<Node> *pieceList) {
	Node *temp = pieceList->start;
	List<Node> *list;
	List<Node> *availableList = new List<Node>;
	while (temp != nullptr) {
		list = makeMovList(temp->piece);
		if (list->start != nullptr) {
			availableList->ins(new Node(temp->piece));
		}
		list->delList();
		temp = temp->next;
	}
	return availableList;
}

List<Node> *PlayerGame::makeAvailableAtkList(List<Node> *pieceList) {
	Node *temp = pieceList->start;
	List<Node> *list;
	List<Node> *availableList = new List<Node>;
	while (temp != nullptr) {
		list = makeAtkList(temp->piece);
		if (list->start != nullptr) {
			availableList->ins(new Node(temp->piece));
		}
		list->delList();
		temp = temp->next;
	}
	return availableList;
}

//CHAIN LIST

List<Node> * PlayerGame::makeChainList(Piece * piece)
{
	List<Node> *chainList = new List<Node>;
	Tile *tile = piece->getTile();
	int pieceType = piece->type;
	addChainList(chainList, tile, pieceType);
	return chainList;
}

void PlayerGame::addChainList(List<Node> *chainList, Tile *tile, int pieceType) {
	if (tile != nullptr) {
		Piece *piece = tile->getPiece();
		if (piece != nullptr) {
			if (piece->type == pieceType) {
				if (!chainList->search(piece)) {
					chainList->ins(new Node(piece));
					addChainList(chainList, tile->getTileNorth(), pieceType);
					addChainList(chainList, tile->getTileSouth(), pieceType);
					addChainList(chainList, tile->getTileWest(), pieceType);
					addChainList(chainList, tile->getTileEast(), pieceType);
				}
			}
		}
	}
}

void PlayerGame::attackChainQ(Piece * piece1, PriorityQueue<AttackNode>* chainQ)
{
	//Chain is now a queue, not a list
	/*Node *temp = chainList->start;
	while (temp != nullptr) {
		attackPiece(piece1, temp->piece);
		temp = temp->next;
	}*/
}

void PlayerGame::attackPieceChainQ(Piece * piece1, Piece * piece2)
{
	anim->animateInitialLaserBeam(piece1, piece2);
	/*List<Node> *chainList = makeChainList(piece2);
	attackChain(piece1, chainList);*/
	/*delete chainList;*/

	//Similar to A *
	int ATK = piece1->stats->ATK;

	PriorityQueue<AttackNode> * traversalQ = new PriorityQueue<AttackNode>;
	traversalQ->enQueue(new AttackNode(ATK, piece1, piece2, 0));
	//fScore is just gScore now

	PriorityQueue<AttackNode> * chainQ = new PriorityQueue<AttackNode>;

	while (!traversalQ->isEmpty()) {
		//std::cout << "****New OUTER LOOP****" << std::endl;
		AttackNode *current = traversalQ->deQueue();
		chainQ->enQueue(current);

		int direction;
		int tentative_fScore = current->fScore + 1;
		for (direction = NORTH; direction <= WEST; direction++) {
			//std::cout << "*new inner loop*" << std::endl;
			//std::cout << direction << std::endl;
			Tile *nextTile = current->piece2->getTile()->getTileDirection(direction);
			if (nextTile == nullptr) {
				//std::cout << "nextTile doesn't exist" << std::endl;
				continue;//skip if doesn't exist (shouldn't happen)
			}
			if (nextTile->getPiece() == nullptr) {
				//std::cout << "nextTile has no piece" << std::endl;
				continue;//skip if no piece
			}
			if (nextTile->getPiece()->type != piece2->type) {
				//std::cout << "nextTile's piece is the wrong type" << std::endl;
				continue;//skip if not same type
			}
			if (chainQ->searchTile(nextTile)) {
				//std::cout << "nextTile already in chainQ" << std::endl;
				continue;//skip if already donezo
			}

			if (!traversalQ->searchTile(nextTile)) {
				AttackNode *newAttack = 
					new AttackNode(ATK, current->piece2, nextTile->getPiece(), tentative_fScore);
				traversalQ->enQueue(newAttack);
			}
			//not sure if necessary since this isn't the same as A *
			else if (tentative_fScore < traversalQ->getSearchTileNode(nextTile)->fScore) {
				AttackNode *existingAttack = traversalQ->getSearchTileNode(nextTile);
				existingAttack->fScore = tentative_fScore;
				existingAttack->piece1 = current->piece2;
			}
		}
	}
	
	delete traversalQ;
	anim->attackQueue->insPQueue(chainQ);
}

//LINE LIST

List<Node> * PlayerGame::makeLineList(Piece * pieceAttacker, Piece * pieceDefender)
{
	//No need for recursion if it's just a straight line
	List<Node> *lineList = new List<Node>;
	//One of these will be zero, one of these will be +/- 1
	int xDirection = pieceDefender->coordinates->x - pieceAttacker->coordinates->x;
	int yDirection = pieceDefender->coordinates->y - pieceAttacker->coordinates->y;

	//int pos[2] = { pieceDefender->pos[0], pieceDefender->pos[1] };
	Vector3<float> *coordinates = new Vector3<float>(pieceDefender->coordinates->x, pieceDefender->coordinates->y);
	while (coordinates->x >= 0 && coordinates->x < gameBoard->ROWS && coordinates->y >= 0 && coordinates->y < gameBoard->COLS) {
		if (gameBoard->getTile(coordinates)->getPiece() == nullptr) {
			break;
		}
		lineList->ins(new Node(gameBoard->getTile(coordinates)->getPiece()));
		coordinates->changeVector(coordinates->x + xDirection, coordinates->y + yDirection);
	}
	delete coordinates;
	return lineList;
}

void PlayerGame::bump(Piece * piece1, Piece * piece2)
{
	List<Node> *lineList = makeLineList(piece1, piece2);
	if (!isBlocked(piece1, lineList)) {
		lineList->reverseList();
		Node *temp = lineList->start;
		while (temp != nullptr) {
			//inevitably, I would need to go back to 4 if statements
			//i could probably overload movePiece though to take the Vector *direction
			//only possibly directions are [1,0], [-1,0], [0,1], [0,-1]
			Vector3<int> *direction = getVectorDirection(piece1, piece2);
			if (direction->x == 1 && direction->y == 0) {//SOUTH
				movePiece(temp->piece, temp->tile->getTileSouth());
			}
			else if (direction->x == -1 && direction->y == 0) {//NORTH
				movePiece(temp->piece, temp->tile->getTileNorth());
			}
			else if (direction->x == 0 && direction->y == 1) {//EAST
				movePiece(temp->piece, temp->tile->getTileEast());
			}
			else if (direction->x == 0 && direction->y == -1) {//WEST
				movePiece(temp->piece, temp->tile->getTileWest());
			}
			temp = temp->next;
		}
	}
	lineList->delList();
}

bool PlayerGame::isBlocked(Piece *pieceAttacker, List<Node> * lineList)
{
	Vector3<int> *direction = getVectorDirection(pieceAttacker, lineList->start->piece);
	Node *end = lineList->getEnd();
	Tile *endTile = getTile(end->tile, direction);
	if (endTile != nullptr) {
		if (endTile->getPiece() == nullptr) {
			return false;
		}
	}
	return true;
}

//DIRECTIONS

Tile * PlayerGame::getTile(Tile * tile, Vector3<int> * direction)
{
	if (direction->x == -1 && direction->y == 0)
		return tile->getTileNorth();
	else if (direction->x == 1 && direction->y == 0)
		return tile->getTileSouth();
	else if (direction->x == 0 && direction->y == -1)
		return tile->getTileWest();
	else if (direction->x == 0 && direction->y == 1)
		return tile->getTileEast();
	else
		return nullptr;
}

Vector3<int> *PlayerGame::getVectorDirection(Piece * piece1, Piece * piece2)
{
	Vector3<int> *direction = 
		new Vector3<int>(piece2->coordinates->x - piece1->coordinates->x,
		piece2->coordinates->y - piece1->coordinates->y);
	return direction;
}

int PlayerGame::getDirection(Piece * piece1, Piece * piece2)
{
	int xDirection = piece2->coordinates->x - piece1->coordinates->x;
	int yDirection = piece2->coordinates->y - piece1->coordinates->y;
	int zDirection = piece2->coordinates->z - piece1->coordinates->z;

	//std::cout << xDirection << " " << yDirection << " " << zDirection;

	if (xDirection > 0)
		return SOUTH;
	else if (xDirection < 0)
		return NORTH;
	else if (yDirection > 0)
		return EAST;
	else if (yDirection < 0)
		return WEST;
	std::cout << "error in getDirection";
	if (zDirection > 0)
		return UP;
	else if (zDirection < 0)
		return DOWN;
	return 0;
}

int PlayerGame::getDirection(Vector3<float>* piece1, Vector3<float>* piece2)
{
	int xDirection = piece2->x - piece1->x;
	int yDirection = piece2->y - piece1->y;
	int zDirection = piece2->z - piece1->z;

	//std::cout << xDirection << " " << yDirection << " " << zDirection;

	if (xDirection > 0)
		return SOUTH;
	else if (xDirection < 0)
		return NORTH;
	else if (yDirection > 0)
		return EAST;
	else if (yDirection < 0)
		return WEST;
	std::cout << "error in getDirection";
	if (zDirection > 0)
		return UP;
	else if (zDirection < 0)
		return DOWN;
	return 0;
}

//GET PRIVATE MEMBERS

GameBoard * PlayerGame::getBoard()
{
	return gameBoard;
}

Renderer * PlayerGame::getRenderer()
{
	return renderer;
}

UIBackend * PlayerGame::getUI()
{
	return ui;
}

KeyInput * PlayerGame::getKeyInput()
{
	return keyIn;
}

Animation * PlayerGame::getAnim()
{
	return anim;
}

//TOOLS FOR GRAPHICS

void PlayerGame::updateCurrentTile()
{
	currentTile = selectTile(selector);
}

void PlayerGame::updatePieceState()
{
	if (currentPiece == nullptr) {
		pieceState = PIECE_INACTIVE;
	}
	else {
		pieceState = PIECE_ACTIVE;
	}
}

void PlayerGame::updateCurrentMovementList()
{
	if (pieceState == PIECE_ACTIVE) {
		if (currentMovementList != nullptr) {
			List<Node> *temp = currentMovementList;
			currentMovementList = nullptr;
			delete temp;
		}
		currentMovementList = makeMovList(currentPiece);
	}
	else {
		if (currentMovementList != nullptr) {
			List<Node> *temp = currentMovementList;
			currentMovementList = nullptr;//dnt know if i need this here, just in case
			delete temp;
		}
		currentMovementList = nullptr;
	}
}

void PlayerGame::updateCurrentAttackList()
{
	if (pieceState == PIECE_ACTIVE) {
		if (currentAttackList != nullptr) {
			List<Node> *temp = currentAttackList;
			currentAttackList = nullptr;
			delete temp;
		}
		currentAttackList = makeAtkList(currentPiece);
	}
	else {
		if (currentAttackList != nullptr) {
			List<Node> *temp = currentAttackList;
			currentAttackList = nullptr;
			delete temp;
		}
		currentAttackList = nullptr;
	}
}