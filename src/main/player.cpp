#include "main/player.hpp"

CPlayer::CPlayer(void)
{
	m_pName=NULL;
	m_pControl=NULL;
}

CPlayer::~CPlayer(void)
{
	if(m_pName!=NULL)
		delete[] m_pName;
	if(m_pControl!=NULL)
		delete m_pControl;
}

void CPlayer::SetName(const char *name)
{
	if(m_pName!=NULL)
		delete[] m_pName;
	m_pName=new char[strlen(name)+1];
	strcpy(m_pName,name);
}
