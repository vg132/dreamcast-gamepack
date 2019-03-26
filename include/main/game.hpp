#ifndef __2E4B621F24D1BD234BE__MENU__HPP__
#define __2E4B621F24D1BD234BE__MENU__HPP__

#include "main/players.hpp"

class CDraw;

class CGame
{
private:
	CDraw *m_pDraw;
	int8 m_iMenuPos;
	uint8 m_iState;
	CPlayers *m_pPlayers;
public:
	static const uint8 STATE_RUN=1;
	static const uint8 STATE_OPTIONS=2;
	static const uint8 STATE_CREDITS=3;
	static const uint8 STATE_LOAD=4;
	static const uint8 STATE_SAVE=5;
	static const uint8 STATE_EXIT=6;

	uint8 GetState(){return(m_iState);};
	void SetState(uint8 state){m_iState=state;};
	CDraw* GetDraw(){return(m_pDraw);};
	uint8 GetMenuPos(){return(m_iMenuPos);};
	void SetMenuPos(uint8 pos){m_iMenuPos=pos;};
	CPlayers* GetPlayers(){return(m_pPlayers);};

	CGame(CDraw *draw);
	~CGame(void);
};

#endif // __2E4B621F24D1BD234BE__MENU__HPP__
