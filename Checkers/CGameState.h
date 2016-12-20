#pragma once
#include "Classes.h"
#include "CGameEngine.h"
class CGameState
{
public:
	virtual void Init() = 0;
	virtual void CleanUp() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void KeyBoard(unsigned char key, int x, int y, CGameEngine *game) = 0;
	virtual void IdleUpdate(CGameEngine *game) = 0;
	virtual void Draw(CGameEngine *game) = 0;

	void ChangeState(CGameEngine *game, CGameState *state);

	CGameState *next;

protected:
	CGameState() {}
};