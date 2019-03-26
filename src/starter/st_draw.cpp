#include "starter/st_draw.hpp"

CSTDraw::CSTDraw(void)
: m_ListFinished(false), xx(0),yy(0)
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

CSTDraw::~CSTDraw(void)
{
	UnloadTextures();
	if(m_pPrint!=NULL)
		delete m_pPrint;
}

void CSTDraw::LoadTextures()
{
	LoadPngTxrToVRAM("/cd/gp/menu/1player.png",&m_MainMenuTextures[0],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/gp/menu/2players.png",&m_MainMenuTextures[1],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/gp/menu/3players.png",&m_MainMenuTextures[2],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/gp/menu/4players.png",&m_MainMenuTextures[3],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/gp/menu/exit.png",&m_MainMenuTextures[4],PNG_FULL_ALPHA);

	LoadPngTxrToVRAM("/cd/gp/starter/background.png",&m_GameTextures[0],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/gp/starter/on.png",&m_GameTextures[1],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/gp/starter/off.png",&m_GameTextures[2],PNG_FULL_ALPHA);

	LoadPngTxrToVRAM("/cd/gp/menu/startermenu.png",&m_BackgroundTexture);
	LoadPngTxrToVRAM("/cd/gp/menu/leftarrow.png",&m_ArrowTexture,PNG_FULL_ALPHA);
}

void CSTDraw::UnloadTextures()
{
	uint8 i(0);
	for(i=0;i<5;i++)
		glDeleteTextures(1,&m_MainMenuTextures[i]);
	for(i=0;i<3;i++)
		glDeleteTextures(1,&m_GameTextures[i]);
	glDeleteTextures(1,&m_ArrowTexture);
	glDeleteTextures(1,&m_BackgroundTexture);
}

void CSTDraw::DrawScene(CSTGame *game)
{
	m_pGame=game;
	m_ListFinished=false;
	glKosBeginFrame();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	if(m_pGame->GetState()==CSTGame::STATE_MENU)
	{
		DrawMenu(m_ArrowTexture,m_BackgroundTexture,m_MainMenuTextures,5,m_pGame->GetMenuPos(),0);
	}
	else if(m_pGame->GetState()==CSTGame::STATE_TEXT)
	{
		if(!m_ListFinished)
			glKosFinishList();
		m_pPrint->Print(320,240,0.0f,0.0f,0.0f,"Get ready to start!",false,CPlPrint::ALIGN_CENTER,25);
	}
	else if((m_pGame->GetState()==CSTGame::STATE_LIGHTS)||
					(m_pGame->GetState()==CSTGame::STATE_GAMEOVER)||
					(m_pGame->GetState()==CSTGame::STATE_START))
	{
		DrawLights();
		if(!m_ListFinished)
			glKosFinishList();
		if(m_pGame->GetResultText()[0]!='\0')
			m_pPrint->Print(320,240,0.0f,0.0f,0.0f,"Results (best time)",false,CPlPrint::ALIGN_CENTER,25);
		m_pPrint->Print(320,240,0.0f,0.0f,0.0f,m_pGame->GetResultText(),false,CPlPrint::ALIGN_CENTER,25);
		if(m_pGame->GetState()==CSTGame::STATE_GAMEOVER)
			m_pPrint->Print(320,440,0.0f,0.0f,0.0f,"Press Start to quit",false,CPlPrint::ALIGN_CENTER,25);
	}
	glKosFinishFrame();
}

void CSTDraw::DrawLights()
{
	PushMatrices();
	SetOrtho();
	DrawBackground(m_GameTextures[0]);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindTexture(GL_TEXTURE_2D, m_GameTextures[1]);
	glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	if((m_pGame->GetTimer()->GetTime()<1000)||(m_pGame->GetState()==CSTGame::STATE_START)||(m_pGame->GetState()==CSTGame::STATE_GAMEOVER))
	{
		glBindTexture(GL_TEXTURE_2D, m_GameTextures[2]);
		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	}
	Rect(74.0f,340.0f,64.0f,64.0f);
	if(m_pGame->GetTimer()->GetTime()<2000)
	{
		glBindTexture(GL_TEXTURE_2D, m_GameTextures[2]);
		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	}
	Rect(185.0f,340.0f,64.0f,64.0f);
	if(m_pGame->GetTimer()->GetTime()<3000)
	{
		glBindTexture(GL_TEXTURE_2D, m_GameTextures[2]);
		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	}
	Rect(289.0f,340.0f,64.0f,64.0f);
	if(m_pGame->GetTimer()->GetTime()<4000)
	{
		glBindTexture(GL_TEXTURE_2D, m_GameTextures[2]);
		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	}
	Rect(394.0f,340.0f,64.0f,64.0f);
	if(m_pGame->GetTimer()->GetTime()<5000)
	{
		glBindTexture(GL_TEXTURE_2D, m_GameTextures[2]);
		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	}
	Rect(501.0f,339.0f,64.0f,64.0f);
	PopMatrices();
}
