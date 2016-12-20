#pragma once
#include "Classes.h"
#include "Structures.h"
#include "PlayerGame.h"
#include "Nodes.h"
#include "Piece.h"
#include "LinkedList.h"
#include "Nodes.h"

/*For simplicity on my part, the AI will first move then attack always.
If no available better movement is available, AI will just attack.
*/

class AI {
public:
	AI();
	AI(PlayerGame *game);
	~AI();
	
	//Move to the position with best attacks
	int scoreBoardMove(int type);

	//Find the best attacks from a position
	int scoreBoardAttack(int type);

	List<Node> *availableMoveThenAttackList(int type);

private:
	PlayerGame *game;
	GameBoard *board;
	List<Node> *playerPieceList;
	List<Node> *cpuPieceList;
};