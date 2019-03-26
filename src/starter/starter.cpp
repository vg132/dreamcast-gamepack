#include "starter/starter.hpp"

CStarter::CStarter(void)
{
	m_pDraw=new CSTDraw();
	m_pControl=new CSTControl();
	m_pGame=new CSTGame();
}

CStarter::~CStarter(void)
{
	delete m_pDraw;
	delete m_pControl;
	delete m_pGame;
}

void CStarter::Run()
{
	uint32 frmctr(0);
	m_pGame->SetState(CSTGame::STATE_MENU);

	while(m_pGame->GetState()!=CSTGame::STATE_EXIT)
	{
		m_pDraw->DrawScene(m_pGame);
		m_pControl->Respond(m_pGame,0,m_pGame->GetPlayers(),frmctr++);
		if((m_pGame->GetState()==CSTGame::STATE_LIGHTS)||(m_pGame->GetState()==CSTGame::STATE_START))
		{
			for(uint8 i=1;i<m_pGame->GetNrOfPlayers();i++)
				m_pControl->Respond(m_pGame,i,m_pGame->GetPlayers(),frmctr++);
		}
		if((m_pGame->GetState()==CSTGame::STATE_TEXT)&&(m_pGame->GetTimer()->GetTime()>2000))
			m_pGame->ChangeState();
		else if((m_pGame->GetState()==CSTGame::STATE_LIGHTS)&&(m_pGame->GetTimer()->GetTime()>(6000+m_pGame->GetLastLightTime())))
			m_pGame->ChangeState();
	}
}

void CStarter::Start(CPlayers *players)
{
	m_pGame->SetPlayers(players);
	m_pGame->SetDraw(m_pDraw);
	Run();
}
