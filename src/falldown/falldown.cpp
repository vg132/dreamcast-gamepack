#include "falldown/falldown.hpp"

CFallDown::CFallDown(void)
{
	m_pDraw=new CFDDraw();
	m_pControl=new CFDControl();
}

CFallDown::~CFallDown(void)
{
	delete m_pControl;
	delete m_pDraw;
}

void CFallDown::Run()
{
	int frmcnt(0);
	
	m_pGame->SetState(CFDGame::STATE_MENU);

	while(m_pGame->GetState()!=CFDGame::STATE_EXIT)
	{
		if(m_pGame->GetState()==CFDGame::STATE_RUN)
			m_pGame->Update();
		m_pDraw->DrawScene(m_pGame);
		m_pControl->Respond(m_pGame,0,m_pGame->GetPlayers(),frmcnt++);
		switch(m_pGame->GetMode())
		{
			case CFDGame::MODE_4PLAYER:
				m_pControl->Respond(m_pGame,3,m_pGame->GetPlayers(),frmcnt++);
			case CFDGame::MODE_3PLAYER:
				m_pControl->Respond(m_pGame,2,m_pGame->GetPlayers(),frmcnt++);
			case CFDGame::MODE_2PLAYER:
				m_pControl->Respond(m_pGame,1,m_pGame->GetPlayers(),frmcnt++);
		}
	}
}

void CFallDown::Start(CPlayers *players)
{
	m_pGame=new CFDGame(m_pDraw,players);
	Run();
	delete m_pGame;
}
