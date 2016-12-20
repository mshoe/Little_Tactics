#include "CGameEngine.h"

CGameEngine::CGameEngine()
{
	Init();
}

CGameEngine::~CGameEngine()
{
	Cleanup();
}

void CGameEngine::Init()
{
	m_running = true;
	states = new Stack<CGameState>;
}

void CGameEngine::Cleanup()
{
	delete states;
}

void CGameEngine::ChangeState(CGameState * state)
{
	states->push(state);
	//more to it
}

void CGameEngine::pushState(CGameState * state)
{
	states->push(state);
}

CGameState * CGameEngine::popState()
{
	CGameState *state = states->pop();
	return state;
}

void CGameEngine::KeyBoard(unsigned char key, int x, int y)
{
	states->top->KeyBoard(key, x, y, this);
}

void CGameEngine::IdleUpdate()
{
	states->top->IdleUpdate(this);
}

void CGameEngine::Draw()
{
	states->top->Draw(this);
}


