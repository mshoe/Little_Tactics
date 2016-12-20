#include "AI.h"

AI::AI()
{
	game = nullptr;
}

AI::AI(PlayerGame * game)
{
	this->game = game;
	this->board = game->getBoard();
	this->playerPieceList = game->playerPieceList;
	this->cpuPieceList = game->cpuPieceList;
}

AI::~AI()
{
}

int AI::scoreBoardMove(int type)
{
	List<Node> *currentPieceList;
	if (type = WHITE)
		currentPieceList = cpuPieceList;
	else {
		currentPieceList = playerPieceList;
	}
	return 0;
}

int AI::scoreBoardAttack(int type)
{
	List<Node> *currentPieceList;
	if (type = WHITE)
		currentPieceList = cpuPieceList;
	else {
		currentPieceList = playerPieceList;
	}

	List<Node> *availableAttackList = game->makeAvailableAtkList(currentPieceList);
	return 0;
}
