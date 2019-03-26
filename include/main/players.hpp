#ifndef __4B6B89DD477BD910FD4752__PLAYERS__HPP__
#define __4B6B89DD477BD910FD4752__PLAYERS__HPP__

#include "main/player.hpp"

class CPlayers
{
private:
	int m_iPlayers;
	CPlayer *m_pPlayers[4];
public:
	int GetPlayers(){return(m_iPlayers);};
	CPlayer* GetPlayer(int id){return(m_pPlayers[id]);};
	CPlayers(void);
	~CPlayers(void);
};

#endif // __4B6B89DD477BD910FD4752__PLAYERS__HPP__
