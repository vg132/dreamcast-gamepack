#ifndef __2528AD3C1DACDEBCE72E5C__SD_GAME__HPP__
#define __2528AD3C1DACDEBCE72E5C__SD_GAME__HPP__

#include <kos.h>
#include <time.h>

#include "sudoku/sd_field.hpp"
#include "main/players.hpp"

class CSSDraw;

class CSDGame
{
private:
	CSDField *m_pField;
	CPlayers *m_pPlayers;
	CSDDraw *m_pDraw;

	uint32 m_StartTime;
	uint32 m_LastTime;
	uint16 m_CursorPos;
	uint8 m_MenuPos;
	uint8 m_State;
public:
	static const uint8 STATE_MENU=0;
	static const uint8 STATE_RUN=1;
	static const uint8 STATE_GAMEOVER=2;
	static const uint8 STATE_EXIT=3;
	static const uint8 STATE_WON=4;

	char* GetTime();
	uint8 GetMenuPos(){return(m_MenuPos);};
	void SetMenuPos(uint8 pos){m_MenuPos=pos;};
	uint8 GetState(){return(m_State);};
	void SetState(int state){m_State=state;};
	uint16 GetCursorPos(){return(m_CursorPos);};
	void SetCursorPos(uint16 pos){m_CursorPos=pos;};
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	CPlayers* GetPlayers(){return(m_pPlayers);};
	CMSField* GetField(){return(m_pField);};
	CMSDraw* GetDraw(){return(m_pDraw);};
	void SetDraw(CMSDraw* draw){m_pDraw=draw;};
	void NewGame(int level);

	CSDGame(void);
	~CSDGame(void);
};


#endif // __2528AD3C1DACDEBCE72E5C__SD_GAME__HPP__
