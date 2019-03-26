#include "pong/pong.hpp"

CPong::CPong(void)
{
	m_pDraw=new CPDraw();
	m_pControl=new CPControl();
	m_pGame=new CPGame();
}

CPong::~CPong(void)
{
	delete m_pDraw;
	delete m_pControl;
	delete m_pGame;
}

void CPong::Run()
{
	uint32 frmctr(0);
	m_pGame->SetState(CPGame::STATE_MENU);

	while(m_pGame->GetState()!=CPGame::STATE_EXIT)
	{
		m_pControl->Respond(m_pGame,0,m_pGame->GetPlayers(),frmctr++);
		if(m_pGame->GetState()==CPGame::STATE_RUN)
		{
			CPBall *ball=m_pGame->GetBall();

			if((ball->GetRect()->GetY()>=27.5f)&&(!ball->GetHit()))
			{
				ball->Bounce(false);
				ball->SetHit(true);
			}
			else if((ball->GetRect()->GetY()-ball->GetRect()->GetHeight()<=-30.5f)&&(!ball->GetHit()))
			{
				ball->Bounce(false);
				ball->SetHit(true);
			}
			else if((ball->GetRect()->GetX()<=-46.0f)&&(!ball->GetHit()))
			{
				ball->Bounce(true);
				ball->SetHit(true);
			}
			else if((ball->GetRect()->GetX()+ball->GetRect()->GetWidth()>=46.0f)&&(!ball->GetHit()))
			{
				ball->Bounce(true);
				ball->SetHit(true);				
			}
			else if(ball->GetHit())
			{
				ball->SetHit(false);
			}
			m_pGame->GetBall()->Move();
		}
		m_pDraw->DrawScene(m_pGame);
	}
}

void CPong::Start(CPlayers *players)
{
	m_pGame->SetPlayers(players);
	m_pGame->SetDraw(m_pDraw);
	Run();
}
