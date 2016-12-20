#pragma once
#include "Classes.h"
#include "Tile.h"
#include "Piece.h"
#include "PlayerGame.h"
#include "GameBoard.h"
#include "LinkedList.h"
#include "Vector3.h"
#include "UIBackend.h"
#include <gl/freeglut.h>
#include <iostream>

class Renderer {
public:
	Renderer();
	Renderer(PlayerGame *);

	float rotation;

	//render tools
	void render(const Tile * tile);
	void renderMovementTiles(const Tile * tile);
	void render(const Piece * piece);
	void renderAttackTiles(const Piece * piece);
	void renderSelector();
	void renderSelectedPiece();
	void renderLaser(Vector3<float> *p1Coords, Piece *piece2, int direction, int ATK);
	void initDisplayLists();

	void renderGame();
	void renderBoard(GameBoard * board, List<Node> * movList, List<Node> * atkList);
	void renderUI();
	void renderPieces(List<Node> *pieceList);
	void renderLasers();
	/*GLuint cpuPiece;
	GLuint playerPiece;
	GLuint lightBrownTile;
	GLuint mediumBrownTile;*/
	GLuint movementTiles;
	GLuint attackTiles;
	GLuint selectedPieceTile;
	GLuint selector;
	GLuint wordMove;
	GLuint wordMoveGrey;
	GLuint wordAttack;
	GLuint wordAttackGrey;
	GLuint wordWait;
	GLuint wordWaitGrey;
	GLuint wordTurn;
	GLuint wordGame;
	
	//Interface
	void renderInt(Vector3<float> *coordinates, Vector3<float> *color, float size, int integer);
	void renderTurnNum(Vector3<float> *coordinates, Vector3<float> *color, float size);
	void renderActionSelector(Vector3<float> *coordinates, Vector3<float> *color, float size);

	//Words
	void renderWordMove(Vector3<float> *coordinates, Vector3<float> *color, float size);
	void renderWordAttack(Vector3<float> *coordinates, Vector3<float> *color, float size);
	void renderWordWait(Vector3<float> *coordinates, Vector3<float> *color, float size);
	void renderWordTurn(Vector3<float> *coordinates, Vector3<float> *color, float size);
	void renderWordGame(Vector3<float> *coordinates, Vector3<float> *color, float size);
	void renderWordAuto(Vector3<float> *coordinates, Vector3<float> *color, float size);
	void renderWordRestart(Vector3<float> *coordinates, Vector3<float> *color, float size);
	void renderWordExit(Vector3<float> *coordinates, Vector3<float> *color, float size);

	//3D Letters
	void renderA(Vector3<float> *coordinates, Vector3<float> *color, float size);
	void renderB(Vector3<float> *coordinates, Vector3<float> *color, float size);
	void renderC(Vector3<float> *coordinates, Vector3<float> *color, float size);
	void renderD(Vector3<float> *coordinates, Vector3<float> *color, float size);
	void renderE(Vector3<float> *coordinates, Vector3<float> *color, float size);
	void renderF(Vector3<float> *coordinates, Vector3<float> *color, float size);
	void renderG(Vector3<float> *coordinates, Vector3<float> *color, float size);
	void renderH(Vector3<float> *coordinates, Vector3<float> *color, float size);
	void renderI(Vector3<float> *coordinates, Vector3<float> *color, float size);
	void renderJ(Vector3<float> *coordinates, Vector3<float> *color, float size);
	void renderK(Vector3<float> *coordinates, Vector3<float> *color, float size);
	void renderL(Vector3<float> *coordinates, Vector3<float> *color, float size);
	void renderM(Vector3<float> *coordinates, Vector3<float> *color, float size);
	void renderN(Vector3<float> *coordinates, Vector3<float> *color, float size);
	void renderO(Vector3<float> *coordinates, Vector3<float> *color, float size);
	void renderP(Vector3<float> *coordinates, Vector3<float> *color, float size);
	void renderQ(Vector3<float> *coordinates, Vector3<float> *color, float size);
	void renderR(Vector3<float> *coordinates, Vector3<float> *color, float size);
	void renderS(Vector3<float> *coordinates, Vector3<float> *color, float size);
	void renderT(Vector3<float> *coordinates, Vector3<float> *color, float size);
	void renderU(Vector3<float> *coordinates, Vector3<float> *color, float size);
	void renderV(Vector3<float> *coordinates, Vector3<float> *color, float size);
	void renderW(Vector3<float> *coordinates, Vector3<float> *color, float size);
	void renderX(Vector3<float> *coordinates, Vector3<float> *color, float size);
	void renderY(Vector3<float> *coordinates, Vector3<float> *color, float size);
	void renderZ(Vector3<float> *coordinates, Vector3<float> *color, float size);
	
	//3D Numbers
	void render0(Vector3<float> *coordinates, Vector3<float> *color, float size);
	void render1(Vector3<float> *coordinates, Vector3<float> *color, float size);
	void render2(Vector3<float> *coordinates, Vector3<float> *color, float size);
	void render3(Vector3<float> *coordinates, Vector3<float> *color, float size);
	void render4(Vector3<float> *coordinates, Vector3<float> *color, float size);
	void render5(Vector3<float> *coordinates, Vector3<float> *color, float size);
	void render6(Vector3<float> *coordinates, Vector3<float> *color, float size);
	void render7(Vector3<float> *coordinates, Vector3<float> *color, float size);
	void render8(Vector3<float> *coordinates, Vector3<float> *color, float size);
	void render9(Vector3<float> *coordinates, Vector3<float> *color, float size);

	void setAnim(Animation *anim);
private:
	PlayerGame *game;
	UIBackend *ui;
	Animation *anim;
};

