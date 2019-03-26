#include "minesweeper/ms_game.hpp"

CMSGame::CMSGame(CPlayers *players)
: m_pField(NULL), m_pDraw(NULL), m_StartTime(0), m_CursorPos(0), m_MenuPos(0)
{
	m_pPlayers=players;
}

CMSGame::~CMSGame(void)
{
	if(m_pField!=NULL)
		delete m_pField;
}

void CMSGame::NewGame(int level)
{
	if(m_pField!=NULL)
		delete m_pField;
	m_pField=NULL;
	switch(level)
	{
		case 2:
			m_pField=new CMSField(30,16,99);
			m_CursorPos=255;
			break;
		case 1:
			m_pField=new CMSField(16,16,40);
			m_CursorPos=136;
			break;
		default:
			m_pField=new CMSField(9,9,10);
			m_CursorPos=40;
			break;
	}
	m_StartTime=0;
}

void CMSGame::Open()
{
	if(m_StartTime==0)
		m_StartTime=time(NULL);
	if((!m_pField->GetTile(m_CursorPos)->IsMarked())&&(!m_pField->GetTile(m_CursorPos)->IsOpen()))
	{
		if(!m_pField->Open(m_CursorPos))
			SetState(CMSGame::STATE_GAMEOVER);
	}
}

void CMSGame::MoveDown()
{
	if(m_CursorPos>=m_pField->GetWidth())
		m_CursorPos-=m_pField->GetWidth();
}

void CMSGame::MoveUp()
{
	if(m_CursorPos<(m_pField->GetTiles()-m_pField->GetWidth()))
		m_CursorPos+=m_pField->GetWidth();
}

void CMSGame::MoveLeft()
{
	if(m_CursorPos%m_pField->GetWidth()!=0)
		m_CursorPos--;
}

void CMSGame::MoveRight()
{
	if((m_CursorPos+1)%m_pField->GetWidth()!=0)
		m_CursorPos++;
}

char* CMSGame::GetTime()
{
	struct tm tm;
	uint32 tmp=0;
	char *buffer=new char[256];
	if(GetState()==CMSGame::STATE_RUN)
		m_LastTime=time(NULL);
	tmp=m_LastTime-m_StartTime;
  localtime_r(&tmp,&tm);
	if(m_StartTime==0)
		sprintf(buffer, "%02d:%02d",0,0);
	else
		sprintf(buffer, "%02d:%02d",tm.tm_min,tm.tm_sec);
	return(buffer);
}

void CMSGame::Mark()
{
	if(m_StartTime==0)
		m_StartTime=time(NULL);
	if(!m_pField->GetTile(m_CursorPos)->IsOpen())
		m_pField->MarkTile(m_CursorPos);
}
