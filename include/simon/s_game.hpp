#ifndef __C76EF160CE5828F530CBFD__S_GAME__HPP__
#define __C76EF160CE5828F530CBFD__S_GAME__HPP__

#include <kos.h>

#include "main/players.hpp"

class CSDraw;

class CSGame
{
private:
	CPlayers *m_pPlayers;
	CSDraw *m_pDraw;

	uint8 m_State;
	uint8 m_Mode;
	uint8 m_MenuPos;
public:
	static const uint8 STATE_MENU=0;
	static const uint8 STATE_RUN=1;
	static const uint8 STATE_GAMEOVER=2;
	static const uint8 STATE_EXIT=3;
	static const uint8 STATE_P1TURN=4;
	static const uint8 STATE_P2TURN=5;
	static const uint8 STATE_P3TURN=6;
	static const uint8 STATE_P4TURN=7;
	static const uint8 STATE_CTURN=8;

	static const uint8 MODE_1PLAYER=0;
	static const uint8 MODE_2PLAYER=1;
	static const uint8 MODE_3PLAYER=2;
	static const uint8 MODE_4PLAYER=3;

	uint8 GetMenuPos(){return(m_MenuPos);};
	void SetMenuPos(uint8 pos){m_MenuPos=pos;};
	uint8 GetMode(){return(m_Mode);};
	void SetMode(uint8 mode){m_Mode=mode;};
	uint8 GetState(){return(m_State);};
	void SetState(uint8 state){m_State=state;};
	CSDraw* GetDraw(){return(m_pDraw);};
	void SetDraw(CSDraw *draw){m_pDraw=draw;};
	CPlayers* GetPlayers(){return(m_pPlayers);};
	void SetPlayers(CPlayers *players){m_pPlayers=players;};

	CSGame(void);
	~CSGame(void);
};

#endif // __C76EF160CE5828F530CBFD__S_GAME__HPP__
