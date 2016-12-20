#pragma once
#include "Classes.h"
#include "PlayerGame.h"
#include "UIBackend.h"
#include "Piece.h"

class KeyInput {
public:
	KeyInput();
	KeyInput(PlayerGame *game);
	~KeyInput();

	bool keyBoardActive;
	void KeyBoard(unsigned char key, int x, int y, CGameEngine *gameEngine);

	void setAnim(Animation *anim);
private:
	PlayerGame *game;
	UIBackend *ui;
	Renderer *renderer;
	Animation *anim;
};