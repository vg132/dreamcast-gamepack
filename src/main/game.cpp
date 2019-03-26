#include "main/game.hpp"

CGame::CGame(CDraw *draw)
{
	m_pDraw=draw;
	m_iMenuPos=0;
	m_pPlayers=new CPlayers();
}

CGame::~CGame(void)
{
	if(m_pPlayers!=NULL)
		delete m_pPlayers;
}
