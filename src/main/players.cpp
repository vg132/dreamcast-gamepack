#include "main/players.hpp"

CPlayers::CPlayers(void)
{
	char buffer[11];
	uint8 maple;
	cont_cond_t cond;
	int i(0);
	m_iPlayers=0;
	for(i=0;i<4;i++)
		m_pPlayers[i]=NULL;
	for(int i=0;i<4;i++)
	{
		maple=maple_create_addr(i,0);
		if(cont_get_cond(maple,&cond)==0)
		{
			m_pPlayers[m_iPlayers]=new CPlayer();
			sprintf(buffer,"Player %d",m_iPlayers+1);
			m_pPlayers[m_iPlayers]->SetName(buffer);
			m_pPlayers[m_iPlayers]->SetControl(new CDCControl(maple));
			m_iPlayers++;
		}
	}
}

CPlayers::~CPlayers(void)
{
	for(int i=0;i<4;i++)
		if(m_pPlayers[i]!=NULL)
			delete m_pPlayers[i];
}
