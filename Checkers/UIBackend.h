#pragma once
#include "Classes.h"
#include "PlayerGame.h"
class UIBackend {
public:
	UIBackend();
	UIBackend(PlayerGame *game);
	~UIBackend();

	int turn;//ODD turn = player, EVEN turn = enemy
	int firstAction;//used to determine what the options are for the second move
	int secondAction;
	int currentAction;
	int actionSelection;
	int leftRightSelection;
private:
	PlayerGame *game;
};