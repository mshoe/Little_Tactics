#pragma once
#include "Classes.h"
#include "Structures.h"
#include "CGameState.h"
#include "Stack.h"

class CGameEngine
{
public:
	CGameEngine();
	~CGameEngine();
	void Init();
	void Cleanup();

	void ChangeState(CGameState *state);
	void pushState(CGameState *state);
	CGameState* popState();

	void KeyBoard(unsigned char key, int x, int y);
	void IdleUpdate();
	void Draw();

	bool Running() { return m_running; }
	void Quit() { m_running = false; }

private:
	//the stack of states
	Stack<CGameState> *states;

	bool m_running;
};