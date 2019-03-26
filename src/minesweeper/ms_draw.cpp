#include "minesweeper/ms_draw.hpp"

CMSDraw::CMSDraw(void)
{
	xx=yy=200;
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

CMSDraw::~CMSDraw(void)
{
	UnloadTextures();
	if(m_pPrint!=NULL)
		delete m_pPrint;
}

void CMSDraw::LoadTextures()
{
	LoadPngTxrToVRAM("/cd/gp/menu/beginner.png",&m_MainMenuTextures[0],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/gp/menu/normal.png",&m_MainMenuTextures[1],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/gp/menu/advanced.png",&m_MainMenuTextures[2],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/gp/menu/exit.png",&m_MainMenuTextures[3],PNG_FULL_ALPHA);

	LoadPngTxrToVRAM("/cd/gp/minesweeper/block.png",&m_GameTextures[0],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/gp/minesweeper/selected.png",&m_GameTextures[1],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/gp/minesweeper/empty_block.png",&m_GameTextures[2],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/gp/minesweeper/block_1.png",&m_GameTextures[3],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/gp/minesweeper/block_2.png",&m_GameTextures[4],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/gp/minesweeper/block_3.png",&m_GameTextures[5],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/gp/minesweeper/block_4.png",&m_GameTextures[6],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/gp/minesweeper/block_5.png",&m_GameTextures[7],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/gp/minesweeper/block_6.png",&m_GameTextures[8],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/gp/minesweeper/block_7.png",&m_GameTextures[9],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/gp/minesweeper/block_8.png",&m_GameTextures[10],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/gp/minesweeper/overlay.png",&m_GameTextures[11],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/gp/minesweeper/marked.png",&m_GameTextures[12],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/gp/minesweeper/marked_selected.png",&m_GameTextures[13],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/gp/minesweeper/mine.png",&m_GameTextures[14],PNG_FULL_ALPHA);

	LoadPngTxrToVRAM("/cd/gp/menu/minesweepermenu.png",&m_BackgroundTextures[0]);

	LoadPngTxrToVRAM("/cd/gp/menu/leftarrow.png",&m_ArrowTexture,PNG_FULL_ALPHA);
}

void CMSDraw::UnloadTextures()
{
	uint8 i(0);
	for(i=0;i<4;i++)
		glDeleteTextures(1,&m_MainMenuTextures[i]);
	for(i=0;i<15;i++)
		glDeleteTextures(1,&m_GameTextures[i]);
	glDeleteTextures(1,&m_ArrowTexture);
	glDeleteTextures(1,&m_BackgroundTextures[0]);

}

void CMSDraw::DrawScene(CMSGame *game)
{
	m_pGame=game;
	m_ListFinished=false;
	glKosBeginFrame();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	if(m_pGame->GetState()==CMSGame::STATE_MENU)
	{
		DrawMenu(m_ArrowTexture,m_BackgroundTextures[0],m_MainMenuTextures,4,m_pGame->GetMenuPos(),20);
	}
	else if(m_pGame->GetState()==CMSGame::STATE_RUN)
	{
		DrawField();
		if(m_ListFinished==false)
			glKosFinishList();
		char *tmp, *buffer;
		tmp=m_pGame->GetTime();
		buffer=new char[256];
		sprintf(buffer,"Time: %s Mines: %d",tmp,m_pGame->GetField()->GetMines()-m_pGame->GetField()->GetMarkedMines());
		m_pPrint->Print(320,447,0.0f,0.0f,0.0f,buffer,false,CPlPrint::ALIGN_CENTER,25);
		delete[] tmp;
		delete[] buffer;
	}
	else if(m_pGame->GetState()==CMSGame::STATE_WON)
	{
		if(m_ListFinished==false)
			glKosFinishList();
		char *tmp, *buffer;
		tmp=m_pGame->GetTime();
		buffer=new char[256];
		sprintf(buffer,"Time: %s Mines: %d",tmp,m_pGame->GetField()->GetMines()-m_pGame->GetField()->GetMarkedMines());
		m_pPrint->Print(320,447,0.0f,0.0f,0.0f,buffer,false,CPlPrint::ALIGN_CENTER,25);
		m_pPrint->Print(320,240,0.0f,0.0f,0.0f,"Congratulations!",false,CPlPrint::ALIGN_CENTER,25);
		m_pPrint->Print(320,270,0.0f,0.0f,0.0f,"You have cleared all mines!!",false,CPlPrint::ALIGN_CENTER,25);
		m_pPrint->Print(320,320,0.0f,0.0f,0.0f,"press any key to continue",false,CPlPrint::ALIGN_CENTER);
		delete[] tmp;
		delete[] buffer;
	}
	else if(m_pGame->GetState()==CMSGame::STATE_GAMEOVER)
	{
		if(m_ListFinished==false)
			glKosFinishList();
		char *tmp, *buffer;
		tmp=m_pGame->GetTime();
		buffer=new char[256];
		sprintf(buffer,"Time: %s Mines: %d",tmp,m_pGame->GetField()->GetMines()-m_pGame->GetField()->GetMarkedMines());
		m_pPrint->Print(320,447,0.0f,0.0f,0.0f,buffer,false,CPlPrint::ALIGN_CENTER,25);
		m_pPrint->Print(320,240,0.0f,0.0f,0.0f,"Game Over!",false,CPlPrint::ALIGN_CENTER,25);
		m_pPrint->Print(320,270,0.0f,0.0f,0.0f,"You hit a mine and faild your mission!",false,CPlPrint::ALIGN_CENTER,25);
		m_pPrint->Print(320,320,0.0f,0.0f,0.0f,"press any key to continue",false,CPlPrint::ALIGN_CENTER);
		delete[] tmp;
		delete[] buffer;
	}
	glKosFinishFrame();
}

void CMSDraw::ResetView()
{
	m_XRot=0.0f;
	m_YRot=0.0f;
	m_Zoom=-27.0f;
}

void CMSDraw::DrawField()
{
	CMSField *field=m_pGame->GetField();
	if(field==NULL)
		return;

	glTranslatef(0.0f,0.0f,m_Zoom);
	glRotatef(m_XRot,1.0f,0.0f,0.0f);
	glRotatef(m_YRot,0.0f,1.0f,0.0f);
	glTranslatef(0-field->GetWidth()/2,0-field->GetHeight()/2,0.0);

	for(int i=0;i<field->GetTiles();i++)
	{
		if((field->GetTile(i)->IsOpen())&&(!field->GetTile(i)->IsMine()))
		{
			switch(field->GetTile(i)->GetMines())
			{
				case 0:
					TexturedRect(m_GameTextures[2],0,0,1,1,1,-1);
					break;
				case 1:
					TexturedRect(m_GameTextures[3],0,0,1,1,1,-1);
					break;
				case 2:
					TexturedRect(m_GameTextures[4],0,0,1,1,1,-1);
					break;
				case 3:
					TexturedRect(m_GameTextures[5],0,0,1,1,1,-1);
					break;
				case 4:
					TexturedRect(m_GameTextures[6],0,0,1,1,1,-1);
					break;
				case 5:
					TexturedRect(m_GameTextures[7],0,0,1,1,1,-1);
					break;
				case 6:
					TexturedRect(m_GameTextures[8],0,0,1,1,1,-1);
					break;
				case 7:
					TexturedRect(m_GameTextures[9],0,0,1,1,1,-1);
					break;
				case 8:
					TexturedRect(m_GameTextures[10],0,0,1,1,1,-1);
					break;
			}
			if((m_pGame->GetCursorPos()==i)&&(m_pGame->GetState()==CMSGame::STATE_RUN))
			{
				glKosFinishList();
				m_ListFinished=true;
				glDepthMask(0);
				glBindTexture(GL_TEXTURE_2D, m_GameTextures[11]);
				Rect(0,0,1,1,0,-0.9f);
				glDepthMask(1);
				
			}
		}
		else if((m_pGame->GetCursorPos()!=i)||(m_pGame->GetState()!=CMSGame::STATE_RUN))
		{
			if(m_pGame->GetState()==CMSGame::STATE_GAMEOVER)
			{
				if(field->GetTile(i)->IsMine())
					TexturedBox(m_GameTextures[14],0,0,1,1,-1);
				else
					TexturedBox(m_GameTextures[0],0,0,1,1,-1);
			}
			else
			{
				if(field->GetTile(i)->IsMarked())
					TexturedBox(m_GameTextures[12],0,0,1,1,-1);
				else
					TexturedBox(m_GameTextures[0],0,0,1,1,-1);
			}
		}
		else if(m_pGame->GetCursorPos()==i)
		{
			if(field->GetTile(i)->IsMarked())
				TexturedBox(m_GameTextures[13],0,0,1,1,-1);
			else
				TexturedBox(m_GameTextures[1],0,0,1,1,-1);
		}
		if(((i+1)%(field->GetWidth()))==0)
		{
			glTranslatef(0-(field->GetWidth()),1.0f,0.0f);
		}
		glTranslatef(1.0f,0.0f,0.0f);
	}
}
