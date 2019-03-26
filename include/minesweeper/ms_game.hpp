#ifndef __A076AA1BA44E3C767224A__MS_GAME__HPP__
#define __A076AA1BA44E3C767224A__MS_GAME__HPP__

#include <kos.h>
#include <time.h>

#include "minesweeper/ms_field.hpp"
#include "main/players.hpp"

class CMSDraw;

class CMSGame
{
private:
	CMSField *m_pField;
	CPlayers *m_pPlayers;
	CMSDraw *m_pDraw;

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
	void Mark();
	void Open();
	CPlayers* GetPlayers(){return(m_pPlayers);};
	CMSField* GetField(){return(m_pField);};
	CMSDraw* GetDraw(){return(m_pDraw);};
	void SetDraw(CMSDraw* draw){m_pDraw=draw;};
	void NewGame(int level);

	CMSGame(CPlayers *players);
	~CMSGame(void);
};

#endif // __A076AA1BA44E3C767224A__MS_GAME__HPP__
