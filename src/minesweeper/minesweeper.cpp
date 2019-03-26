#include "minesweeper/minesweeper.hpp"

CMinesweeper::CMinesweeper(void)
{
	m_pDraw=new CMSDraw();
	m_pControl=new CMSControl();
}

CMinesweeper::~CMinesweeper(void)
{
	delete m_pControl;
	delete m_pDraw;
}

void CMinesweeper::Run()
{
	uint32 frmctr(0);
	m_pGame->SetState(CMSGame::STATE_MENU);

	while(m_pGame->GetState()!=CMSGame::STATE_EXIT)
	{
		m_pDraw->DrawScene(m_pGame);
		m_pControl->Respond(m_pGame,0,m_pGame->GetPlayers(),frmctr++);
		if((m_pGame->GetState()==CMSGame::STATE_RUN)&&(m_pGame->GetField()->HasWon()))
			m_pGame->SetState(CMSGame::STATE_WON);
	}
}

void CMinesweeper::Start(CPlayers *players)
{
	m_pGame=new CMSGame(players);
	m_pGame->SetDraw(m_pDraw);
	Run();
	delete m_pGame;
}
