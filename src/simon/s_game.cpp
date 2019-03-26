#include "simon/s_game.hpp"

CSGame::CSGame(void)
:m_pPlayers(NULL), m_pDraw(NULL),m_State(CSGame::STATE_MENU),m_Mode(CSGame::MODE_1PLAYER),m_MenuPos(0)
{
}

CSGame::~CSGame(void)
{
}
