#include "Animation.h"

Animation::Animation()
{
	movementQueue = new Queue<MovementNode>;
	movementStack = new Stack<MovementNode>;
	attackQueue = new PriorityQueue<AttackNode>;

	isAnimatingMovement = false;
	isAnimatingAttack = false;

	game = nullptr;
	keyIn = game->getKeyInput();
}

Animation::Animation(PlayerGame * game)
{
	movementQueue = new Queue<MovementNode>;
	movementStack = new Stack<MovementNode>;
	attackQueue = new PriorityQueue<AttackNode>;

	isAnimatingMovement = false;
	isAnimatingAttack = false;

	this->game = game;
	keyIn = game->getKeyInput();
}

Animation::~Animation()
{
	delete movementQueue;
	delete movementStack;
	delete attackQueue;
}

//A *
Queue<MovementNode>* Animation::aStar(Piece * piece, Tile * finalTile)
{
	//std::cout << "****New Path Find****" << std::endl;
	List<MovementNode> *closedList = new List<MovementNode>;
	PriorityQueue<MovementNode> *openQueue = new PriorityQueue<MovementNode>;
	//cameFrom member in MovementNode

	//(piece, tile, gScore, fScore

	openQueue->enQueue(new MovementNode(piece, piece->getTile(), 0, HeuristicAStar(piece->getTile(), finalTile)));

	while (!openQueue->isEmpty()) {
		//std::cout << "test1" << std::endl;
		MovementNode *current = openQueue->deQueue();
		closedList->ins(current);
		if (current->tile == finalTile) {
			//clean up first

			Queue<MovementNode> *aStarPath = reConstructPath(current, closedList);
			delete closedList;//nodes in closed list that are also in path are taken out of closed list in reConstructPath
			delete openQueue;
			return aStarPath;
		}

		//checking each of the 4 neighbors
		int direction;
		for (direction = NORTH; direction <= WEST; direction++) {
			int tentative_gScore = current->gScore + 1;
			//std::cout << direction << " " << tentative_gScore << std::endl;
			Tile *nextTile = current->tile->getTileDirection(direction);
			if (nextTile == nullptr) {
				//std::cout << "next tile was null" << std::endl;
				continue;//ignore the nonexistent
			}
			if (nextTile->getPiece() != nullptr) {
				//std::cout << "next tile had a piece" << std::endl;
				continue;//can't move through pieces
			}
			if (closedList->search(nextTile)) {
				//std::cout << "next tile was in closed list" << std::endl;
				continue;//ignore which is already evaluated
			}
			//distance from start to a neighbor
			if (!openQueue->searchTile(nextTile)) {
				//std::cout << "next tile is being added to openQueue" << std::endl;
				//std::cout << "Q size before :" << openQueue->size << std::endl;
				MovementNode *newNode =
					new MovementNode(piece, nextTile, tentative_gScore, tentative_gScore + HeuristicAStar(nextTile, finalTile));
				newNode->cameFrom = current;
				openQueue->enQueue(newNode);
				//std::cout << "Q size after :" << openQueue->size << std::endl;
			}
			else if (tentative_gScore < openQueue->getSearchTileNode(nextTile)->gScore) {
				//std::cout << "next tile is already in Queue, but this one has a better score" << std::endl;
				MovementNode *existingNode = openQueue->getSearchTileNode(nextTile);
				existingNode->gScore = tentative_gScore;
				existingNode->fScore = tentative_gScore + HeuristicAStar(nextTile, finalTile);
				existingNode->cameFrom = current;
			}
			else {
				continue;//this is not a better path
			}
		}
	}

	std::cout << "A * failed" << std::endl;
	return nullptr;//failure
}

Queue<MovementNode>* Animation::reConstructPath(MovementNode * MN, List<MovementNode> *closedList)
{
	Queue<MovementNode> *constructedPath = new Queue<MovementNode>;
	Stack<MovementNode> *pathStack = new Stack<MovementNode>;

	//Stack is for reversing
	//Stack is necessary since this isn't a priority queue

	MovementNode *temp = MN;

	//pushing the path onto the stack
	while (temp != nullptr) {
		if (closedList->search(temp->tile)) {
			closedList->delSearchTileNode(temp->tile);//takes the node with that tile out of the list
		}
		pathStack->push(temp);
		temp = temp->cameFrom;
	}

	//queueing the path into the queue
	while (!pathStack->isEmpty()) {
		temp = pathStack->pop();
		constructedPath->enQueue(temp);
	}

	delete pathStack;
	return constructedPath;
}

int Animation::HeuristicAStar(Tile * tile1, Tile * tile2)
{
	int xCost = tile2->coordinates->x - tile1->coordinates->x;
	int yCost = tile2->coordinates->y - tile1->coordinates->y;
	int zCost = tile2->coordinates->z - tile1->coordinates->z;
	return Math::abs(xCost) + Math::abs(yCost) + Math::abs(zCost);
}


//ANIMATION

void Animation::animateOneLaserBeam(Piece * piece1, Piece * piece2)
{
	int direction = game->getDirection(piece1, piece2);
	//piece1->facing = direction;
}

void Animation::animateInitialLaserBeam(Piece * piece1, Piece * piece2)
{
	int direction = game->getDirection(piece1, piece2);
	piece1->facing = direction;
}

void Animation::animateOneMovement(Piece * piece, Tile * finalTile)
{
	//only used for 1 tile movements

	//take the piece off the first tile
	Tile *initialTile = piece->getTile();
	initialTile->changePiece(nullptr);

	float speed = 25.f;
	Vector3<float> *origin = piece->coordinates;
	Vector3<float> *dest = finalTile->coordinates;
	Vector3<float> *direction = new Vector3<float>(dest->x - origin->x,
		dest->y - origin->y,
		dest->z - origin->z);

	bool pastFinishLine = false;

	if (direction->x > 0.f) {
		piece->facing = SOUTH;
		piece->coordinates->x += speed * game->elapsedTime;
		if (piece->coordinates->x > dest->x)
			pastFinishLine = true;
	}
	else if (direction->x < 0.f) {
		piece->facing = NORTH;
		piece->coordinates->x -= speed * game->elapsedTime;
		if (piece->coordinates->x < dest->x)
			pastFinishLine = true;
	}
	if (direction->y > 0.f) {
		piece->facing = EAST;
		piece->coordinates->y += speed * game->elapsedTime;
		if (piece->coordinates->y > dest->y)
			pastFinishLine = true;
	}
	else if (direction->y < 0.f) {
		piece->facing = WEST;
		piece->coordinates->y -= speed * game->elapsedTime;
		if (piece->coordinates->y < dest->y)
			pastFinishLine = true;
	}

	if (direction->z > 0.f)
		piece->coordinates->z += speed * game->elapsedTime;
	else if (direction->z < 0.f)
		piece->coordinates->z -= speed * game->elapsedTime;

	delete direction;
	piece->updateVertices();
	
	if (piece->coordinates->compareVectorWithPrecision(dest, 0.01f) || pastFinishLine) {
		isAnimatingMovement = false;
		finalTile->changePiece(piece);
	}
}

void Animation::animateOneAttack(int ATK, Piece *piece1, Piece * piece2)
{
	float speed = ATK * 2.f;
	float finalSize;

	if (piece2->stats->HP - ATK <= 0)
		finalSize = 0.f;
	else if (piece2->stats->HP - ATK == 1)
		finalSize = piece2->getFullSize() * 0.667f;
	else
		finalSize = piece2->getFullSize();

	piece2->size -= speed * game->elapsedTime;
	if (piece2->size <= finalSize) {
		isAnimatingAttack = false;
		piece2->size = finalSize;
		piece2->stats->HP -= ATK;
		if (piece2->stats->HP <= 0) {
			game->delPiece(piece2);
			return;//necessary to avoid updating vertices of deleted piece
		}
	}
	piece2->updateVertices();
}

void Animation::animateOneMovementFromStack()
{
	//WILL USE A STACK FOR BUMPS
	animateOneMovement(movementStack->top->piece, movementStack->top->tile);
}

void Animation::animateOneMovementFromQueue()
{
	animateOneMovement(movementQueue->front->piece, movementQueue->front->tile);
}

void Animation::animateOneAttackFromQueue()
{
	animateOneAttack(attackQueue->front->ATK,
		attackQueue->front->piece1,
		attackQueue->front->piece2);
}

void Animation::animateMovementStack()
{
	if (!isMovementStackEmpty()) {
		isAnimatingMovement = true;
		animateOneMovementFromStack();
		if (isAnimatingMovement == false) {
			MovementNode *temp = movementStack->pop();
			delete temp;
		}
	}
}

void Animation::animateMovementQueue()
{
	if (!isMovementQueueEmpty()) {
		game->getKeyInput()->keyBoardActive = false;
		isAnimatingMovement = true;
		animateOneMovementFromQueue();
		if (isAnimatingMovement == false) {
			game->getKeyInput()->keyBoardActive = true;
			MovementNode *temp = movementQueue->deQueue();
			delete temp;
		}
	}
}

void Animation::animateAttackQueue()
{
	if (!isAttackQueueEmpty()) {
		keyIn->keyBoardActive = false;
		isAnimatingAttack = true;
		animateOneAttackFromQueue();
		if (isAnimatingAttack == false) {
			keyIn->keyBoardActive = true;
			AttackNode *temp = attackQueue->deQueue();
			delete temp;
			game->updateStats();
		}
	}
}

bool Animation::isMovementStackEmpty()
{
	if (movementStack->size == 0)
		return true;
	return false;
}

bool Animation::isMovementQueueEmpty()
{
	if (movementQueue->size == 0)
		return true;
	else if (movementQueue->size > 0)
		return false;
	else
		return true;//test
}

bool Animation::isAttackQueueEmpty()
{
	if (attackQueue->size <= 0)
		return true;
	return false;
}