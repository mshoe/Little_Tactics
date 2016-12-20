#pragma once
#include "Classes.h"
#include "Structures.h"
#include "CGameEngine.h"
#include "CGameState.h"
#include "GameBoard.h"
#include "LinkedList.h"
#include "Queue.h"
#include "PriorityQueue.h"
#include "Piece.h"
#include "Vector3.h"
#include "Renderer.h"
#include "Nodes.h"
#include "Math.h"
#include "UIBackend.h"
#include "KeyInput.h"
#include "AI.h"
#include "Animation.h"
#include <chrono>

typedef std::chrono::high_resolution_clock Clock;

//Piece.h has direction enum

class PlayerGame : public CGameState {
public:
	PlayerGame();

	//Inherited Members
	void Init();
	void CleanUp();
	void Pause();
	void Resume();
	void KeyBoard(unsigned char key, int x, int y, CGameEngine *gameEngine);
	void IdleUpdate(CGameEngine *gameEngine);
	void Draw(CGameEngine *gameEngine);


	//FUNDAMENTAL ACTIONS
	void movePiece(Piece *piece, Tile *tile);
	void attackPiece(int ATK, Piece *piece1, Piece *piece2);//piece1 chains the attack laser
	void delPiece(Piece *piece);
	void updateStats();
	void updatePieceListStats(List<Node> *pieceList);
	void nextTurn();
	void restart();

	//MISC. TOOLS
	int checkWinner();
	int getType();
	int getOppType();
	Tile *selectTile(Vector3<float> *coordinates);
	bool correctTurn(Piece *piece);
	bool availableMoves();
	bool availableAttacks();

	//Basic Piece Lists
	List<Node> *makeMovList(Piece *piece);//Breadth-first instead of depth-first to avoid 
	//a major error that gives less range in 3 of the directions
	List<Node> *makeAjcAllyList(Piece *piece);
	void addPieceAjcList(Tile *tile, List<Node> *ajcList, int type);
	List<Node> *makeAtkList(Piece *piece);
	List<Node> *makePieceList(int type);
	List<Node> *makeAvailableMovList(List<Node> *pieceList);
	List<Node> *makeAvailableAtkList(List<Node> *pieceList);

	//Chain List
	List<Node> *makeChainList(Piece *piece);
	void addChainList(List<Node> *chainList, Tile *tile, int pieceType);

	//Attack Chain (Queue, not list)
	void attackChainQ(Piece *piece1, PriorityQueue<AttackNode> *chainQ);
	void attackPieceChainQ(Piece *piece1, Piece *piece2);

	//Line List, measured in direction of attacker to defender
	List<Node> *makeLineList(Piece *pieceAttacker, Piece *pieceDefender);
	void bump(Piece *piece1, Piece *piece2);
	bool isBlocked(Piece *pieceAttacker, List<Node> *lineList);
	
	//directions
	Tile *getTile(Tile *tile, Vector3<int> *direction);//get the tile in the specific direction
	Vector3<int> *getVectorDirection(Piece *piece1, Piece *piece2);//used in LineList functions
	int getDirection(Piece *piece1, Piece *piece2);//will be used to determine directions from 1 block away
	int getDirection(Vector3<float> *piece1, Vector3<float> *piece2);

	//GET PRIVATE MEMBERS
	GameBoard *getBoard();
	Renderer *getRenderer();
	UIBackend *getUI();
	KeyInput *getKeyInput();
	Animation *getAnim();

	//TOOLS FOR GRAPHIS
	void updateCurrentTile();
	void updatePieceState();
	void updateCurrentMovementList();
	void updateCurrentAttackList();

	//Objects and Values
	Vector3<float> *selector;
	int selectorState;
	Piece *currentPiece;
	Piece *piece1;//for attacking
	Piece *piece2;//for getting attacked
	int pieceState;
	int winner;
	Tile *currentTile;
	List<Node> *currentMovementList;
	List<Node> *currentAttackList;
	List<Node> *playerPieceList;
	List<Node> *cpuPieceList;

	//Timer
	double elapsedTime;

private:
	GameBoard *gameBoard;
	Renderer *renderer;
	UIBackend *ui;
	KeyInput *keyIn;
	AI *ai;
	Animation *anim;
};

enum action {
	TURN_START = 0, 
	FIRST_ACTION = 1, 
	ATTACK_OR_MOVE = 2,
	MOVE_TILES = 3,
	ATTACK_TILES = 4,
	MOVE_SELECTION = 5, 
	ATTACK_SELECTION = 6,
	SECOND_ACTION = 7,
	TURN_END = 8
};

enum selectorState {
	SELECTOR_INACTIVE = 0,
	SELECTOR_ACTIVE = 1
};

enum pieceState {
	PIECE_INACTIVE = 0,
	PIECE_ACTIVE = 1
};

enum actionSelection {
	MOVE = 1,
	ATTACK = 2,
	WAIT = 3
};

enum leftMenuSelection {
	AUTO = 1,
	RESTART = 2,
	EXIT = 3
};

enum leftRightSelection {
	LEFT = 1,
	RIGHT = 2
};

enum pieceType {
	WHITE = 0,
	BLACK = 1
};