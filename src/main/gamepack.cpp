#include "main/gamepack.hpp"

CGamePack::CGamePack(void)
{
}

CGamePack::~CGamePack(void)
{
}

void CGamePack::Start()
{
	m_pControl=new CControl();
	m_pDraw=new CDraw();
	m_pDraw->GLInit();
	m_pDraw->LoadMainTextures();

	m_pGame=new CGame(m_pDraw);

	//Init random
	time_t t;
	t=time(NULL);
	srand(t);

	int frmctr(0);
	while(m_pGame->GetState()!=CGame::STATE_EXIT)
	{
		m_pDraw->DrawScene(m_pGame);
		m_pControl->Respond(m_pGame,m_pGame->GetPlayers()->GetPlayer(0)->GetControl(),++frmctr);
	}
	delete m_pGame;
	delete m_pControl;
	delete m_pDraw;
}
