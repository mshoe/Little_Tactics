#pragma once
#include "Classes.h"
#include "PlayerGame.h"

class Animation {
public:
	Animation();
	Animation(PlayerGame *game);
	~Animation();

	//A *
	Queue<MovementNode> *aStar(Piece *piece, Tile *finalTile);
	Queue<MovementNode> *reConstructPath(MovementNode *MN, List<MovementNode> *closedList);
	int HeuristicAStar(Tile *tile1, Tile *tile2);

	//ANIMATION
	void animateOneLaserBeam(Piece *piece1, Piece *piece2);
	void animateInitialLaserBeam(Piece *piece1, Piece *piece2);
	void animateOneMovement(Piece *piece, Tile *finalTile);
	void animateOneAttack(int ATK, Piece *piece1, Piece *piece2);
	void animateOneMovementFromStack();
	void animateOneMovementFromQueue();
	void animateOneAttackFromQueue();
	void animateMovementStack();
	void animateMovementQueue();
	void animateAttackQueue();
	bool isMovementStackEmpty();
	bool isMovementQueueEmpty();
	bool isAttackQueueEmpty();
	bool isAnimatingMovement;
	bool isAnimatingAttack;
	Stack<MovementNode> *movementStack;
	Queue<MovementNode> *movementQueue;
	PriorityQueue<AttackNode> *attackQueue;

private:
	PlayerGame *game;
	KeyInput *keyIn;
};