#include "pong/p_game.hpp"

CPGame::CPGame(void)
: m_pPlayers(NULL), m_pDraw(NULL), m_pBall(NULL), m_MenuPos(0),m_State(CPGame::STATE_MENU),m_Mode(CPGame::MODE_1PLAYER)
{
}

CPGame::~CPGame(void)
{
	if(m_pBall!=NULL)
		delete m_pBall;
}

void CPGame::NewGame()
{
	if(m_pBall!=NULL)
		delete m_pBall;
	m_pBall=new CPBall(2.0f,-2.0f,1.0f,-0.2f,0.2f);
}
