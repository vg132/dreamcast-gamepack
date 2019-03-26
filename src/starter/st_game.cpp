#include "starter/st_game.hpp"

CSTGame::CSTGame()
: m_pDraw(NULL), m_MenuPos(0), m_State(0), m_Players(0)
{
	m_pStarterPlayers=new CSTPlayer[4];
	m_ResultText=new char[400];
}

CSTGame::~CSTGame(void)
{
	delete[] m_pStarterPlayers;
	delete[] m_ResultText;
}

void CSTGame::NewGame(uint8 players)
{
	uint8 i=0;
	m_Players=players;
	for(i=0;i<players;i++)
		m_pStarterPlayers[i].SetPlaying(true);
	for(i=players+1;i<4;i++)
		m_pStarterPlayers[i].SetPlaying(false);
	SetState(CSTGame::STATE_TEXT);
	m_ResultText[0]='\0';
	m_Timer.Start();
}

void CSTGame::ChangeState()
{
	switch(GetState())
	{
		case CSTGame::STATE_TEXT:
			SetState(CSTGame::STATE_LIGHTS);
			m_Timer.Stop();
			m_Timer.Start();
			break;
		case CSTGame::STATE_LIGHTS:
			SetState(CSTGame::STATE_START);
			m_Timer.Stop();
			m_Timer.Start();
			break;
	}
}

uint16 CSTGame::Random(uint16 limit)
{
	return((rand())%limit);
}

void CSTGame::Stopped(uint8 player)
{
	if(!m_pStarterPlayers[player].IsPlaying())
		return;
	char tmp[100];
	char *tmp2;
	if(GetState()==CSTGame::STATE_START)
	{
		tmp2=m_Timer.GetTimeStringMs();
		m_pStarterPlayers[player].SetBestTime(m_Timer.GetTime(),tmp2);
		sprintf(tmp,"\nPlayer %d - %s (%s)",(player+1),tmp2,m_pStarterPlayers[player].GetBestTimeString());
		delete[] tmp2;
	}
	else
	{
		sprintf(tmp,"\nPlayer %d - Jump start!",(player+1));
	}
	m_pStarterPlayers[player].SetPlaying(false);
	strcat(m_ResultText,tmp);
	for(uint8 i=0;i<m_Players;i++)
	{
		if(m_pStarterPlayers[i].IsPlaying())
			return;
	}
	SetState(CSTGame::STATE_GAMEOVER);
}
