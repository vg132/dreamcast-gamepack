#include "simon/s_draw.hpp"

CSDraw::CSDraw(void)
{
	m_pPrint=new CPlPrint();
	m_pPrint->SetFont("/cd/gp/font/helvetica_medium.txf");

	LoadTextures();
	glKosInit();
	SetPerspective();

	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_FILTER, GL_FILTER_BILINEAR);
}

CSDraw::~CSDraw(void)
{
	UnloadTextures();
	delete m_pPrint;
}

void CSDraw::LoadTextures()
{
	LoadPngTxrToVRAM("/cd/gp/menu/1player.png",&m_MainMenuTextures[0],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/gp/menu/2players.png",&m_MainMenuTextures[1],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/gp/menu/3players.png",&m_MainMenuTextures[2],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/gp/menu/4players.png",&m_MainMenuTextures[3],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/gp/menu/exit.png",&m_MainMenuTextures[4],PNG_FULL_ALPHA);

	LoadPngTxrToVRAM("/cd/gp/menu/simonmenu.png",&m_BackgroundTexture);
	LoadPngTxrToVRAM("/cd/gp/menu/leftarrow.png",&m_ArrowTexture,PNG_FULL_ALPHA);
}

void CSDraw::UnloadTextures()
{
	uint8 i;
	for(i=0;i<5;i++)
		glDeleteTextures(1,&m_MainMenuTextures[i]);
	glDeleteTextures(1,&m_ArrowTexture);
	glDeleteTextures(1,&m_BackgroundTexture);
}

void CSDraw::DrawScene(CSGame *game)
{
	m_pGame=game;
	m_ListFinished=false;
	glKosBeginFrame();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	if(m_pGame->GetState()==CSGame::STATE_MENU)
	{
		DrawMenu(m_ArrowTexture,m_BackgroundTexture,m_MainMenuTextures,5,m_pGame->GetMenuPos(),0);
	}
	glKosFinishFrame();
}