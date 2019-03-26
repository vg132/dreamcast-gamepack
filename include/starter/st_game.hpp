#ifndef __26871C53BB16A27726B85__ST_GAME__HPP__
#define __26871C53BB16A27726B85__ST_GAME__HPP__

#include <kos.h>
#include <stdlib.h>

#include "dccommon/timer.hpp"

#include "main/players.hpp"
#include "starter/st_player.hpp"

class CSTDraw;

class CSTGame
{
private:
	CSTDraw *m_pDraw;
	CPlayers *m_pPlayers;
	CSTPlayer *m_pStarterPlayers;
	CTimer m_Timer;

	char *m_ResultText;
	uint8 m_MenuPos;
	uint8 m_State;
	uint8 m_Players;
	uint16 m_LastLightTime;

	uint16 Random(uint16 limit);
public:
	static const uint8 STATE_MENU=0;
	static const uint8 STATE_TEXT=1;
	static const uint8 STATE_GAMEOVER=2;
	static const uint8 STATE_EXIT=3;
	static const uint8 STATE_LIGHTS=4;
	static const uint8 STATE_START=5;

	uint8 GetMenuPos(){return(m_MenuPos);};
	void SetMenuPos(uint8 pos){m_MenuPos=pos;};
	uint8 GetState(){return(m_State);};
	void SetState(uint8 state){m_State=state;};
	CSTDraw* GetDraw(){return(m_pDraw);};
	void SetDraw(CSTDraw *draw){m_pDraw=draw;};
	CPlayers* GetPlayers(){return(m_pPlayers);};
	void SetPlayers(CPlayers *players){m_pPlayers=players;};
	void NewGame(uint8 players);
	uint8 GetNrOfPlayers(){return(m_Players);};
	CTimer* GetTimer(){return(&m_Timer);};
	void ChangeState();
	uint16 GetLastLightTime(){return(m_LastLightTime);};
	void Stopped(uint8 player);
	char* GetResultText(){return(m_ResultText);};

	CSTGame(void);
	~CSTGame(void);
};


#endif // __26871C53BB16A27726B85__ST_GAME__HPP__
