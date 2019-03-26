#include "simon/simon.hpp"

CSimon::CSimon(void)
{
	m_pDraw=new CSDraw();
	m_pControl=new CSControl();
	m_pGame=new CSGame();
}

CSimon::~CSimon(void)
{
	delete m_pDraw;
	delete m_pControl;
	delete m_pGame;
}

void CSimon::Run()
{
	uint32 frmctr(0);
	m_pGame->SetState(CSGame::STATE_MENU);

	while(m_pGame->GetState()!=CSGame::STATE_EXIT)
	{
		m_pDraw->DrawScene(m_pGame);
		m_pControl->Respond(m_pGame,0,m_pGame->GetPlayers(),frmctr++);
	}
}

void CSimon::Start(CPlayers *players)
{
	m_pGame->SetPlayers(players);
	m_pGame->SetDraw(m_pDraw);
	Run();
}
