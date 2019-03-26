#ifndef __FE96C97A4941F9B28F326F__FD_GAME__HPP__
#define __FE96C97A4941F9B28F326F__FD_GAME__HPP__

#include <kos.h>
#include <arch/rtc.h>
#include "dccommon/dccontrol.hpp"

#include "falldown/fd_field.hpp"
#include "falldown/fd_ball.hpp"

#include "main/players.hpp"

class CFDDraw;

class CFDGame
{
private:
	CFDField *m_pField;
	CFDBall *m_pBall[4];
	CFDDraw *m_pDraw;
	CPlayers *m_pPlayers;

	uint8 m_iLevel;
	uint8 m_iState;
	uint8 m_iMode;
	uint16 m_iSpeed;
	uint16 m_iBlockSpeed;
	uint32 m_iPoints;
	uint8 m_iMenuPos;
	uint8 m_iPauseMenuPos;
public:
	static const uint8 STATE_MENU=0;
	static const uint8 STATE_RUN=1;
	static const uint8 STATE_GAMEOVER=2;
	static const uint8 STATE_EXIT=3;
	static const uint8 STATE_PAUSE=4;

	static const uint8 MODE_1PLAYER=0;
	static const uint8 MODE_2PLAYER=1;
	static const uint8 MODE_3PLAYER=2;
	static const uint8 MODE_4PLAYER=3;

	CFDBall* CFDGame::CheckCollision(CFDBall *ball);

	void SetMode(uint8 mode){m_iMode=mode;};
	uint8 GetMode(){return(m_iMode);};
	uint8 GetState(){return(m_iState);};
	void SetState(uint8 state){m_iState=state;};
	int GetLevel(){return(m_iLevel);};
	void NewGame();
	void Update();

	uint8 GetMenuPos(){return(m_iMenuPos);};
	void SetMenuPos(uint8 i){m_iMenuPos=i;};

	uint8 GetPauseMenuPos(){return(m_iPauseMenuPos);};
	void SetPauseMenuPos(uint8 i){m_iPauseMenuPos=i;};

	void MoveLeft(uint8 player);
	void MoveRight(uint8 player);

	CFDField* GetField(){return(m_pField);};
	CFDBall* GetBall(uint8 id){return(m_pBall[id]);};
	CFDDraw* GetDraw(){return(m_pDraw);};
	CPlayers* GetPlayers(){return(m_pPlayers);};

	CFDGame(CFDDraw *draw, CPlayers *players);
	~CFDGame(void);
};

#endif // __FE96C97A4941F9B28F326F__FD_GAME__HPP__
