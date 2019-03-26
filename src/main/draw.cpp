#include "main/draw.hpp"

CDraw::CDraw(void)
{
	xx=290.0f;
	yy=220.0f;
}

CDraw::~CDraw(void)
{
}

void CDraw::GLInit()
{
	glKosInit();

	SetPerspective();

	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_FILTER, GL_FILTER_NONE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_FILTER, GL_FILTER_BILINEAR);
}

void CDraw::LoadMainTextures()
{
	//LoadPngTxrToVRAM("/cd/gp/menu/mainscreen.png",&m_iBackground);
	LoadPngTxrToVRAM("/rd/mainscreen2.png",&m_iBackground);
	LoadPngTxrToVRAM("/rd/left_arrow.png",&m_iLeftArrow,PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/rd/right_arrow.png",&m_iRightArrow,PNG_FULL_ALPHA);
}

void CDraw::UnloadMainTextures()
{
	glDeleteTextures(1,&m_iBackground);
	glDeleteTextures(1,&m_iLeftArrow);
	glDeleteTextures(1,&m_iRightArrow);
}

void CDraw::DrawScene(CGame *game)
{
	m_pGame=game;
	glKosBeginFrame();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	DrawMainMenu();

	glKosFinishFrame();
}

void CDraw::DrawMainMenu()
{
	DrawBackground(m_iBackground);
	glKosFinishList();

	PushMatrices();
	SetOrtho();

	if((m_pGame->GetMenuPos()%2)==0)
		TexturedRect(m_iLeftArrow,280.0f,320.0f-(floor(m_pGame->GetMenuPos()/2)*60) ,32.0f,32.0f);
	else
		TexturedRect(m_iRightArrow,310.0f,320.0f-(floor(m_pGame->GetMenuPos()/2)*60),32.0f,32.0f);

	PopMatrices();
}
