#include "starter/st_player.hpp"

CSTPlayer::CSTPlayer(void)
: m_BestTime(0)
{
	m_BestTimeString=NULL;
}

CSTPlayer::~CSTPlayer(void)
{
	if(m_BestTimeString!=NULL)
		delete[] m_BestTimeString;
}

void CSTPlayer::SetBestTime(uint64 time, char *timeString)
{
	if((time<m_BestTime)||(m_BestTime==0))
	{
		m_BestTime=time;
		if(m_BestTimeString!=NULL)
			delete[] m_BestTimeString;
		m_BestTimeString=new char[strlen(timeString)+1];
		strcpy(m_BestTimeString,timeString);
	}
}