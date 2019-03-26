#ifndef __89FCC6E62458C847A92B21__P_GAME__HPP__
#define __89FCC6E62458C847A92B21__P_GAME__HPP__

#include <kos.h>

#include "dccommon/rect.hpp"
#include "main/players.hpp"
#include "pong/p_ball.hpp"
#include "pong/p_paddle.hpp"

class CPDraw;

class CPGame
{
private:
	CPlayers *m_pPlayers;
	CPDraw *m_pDraw;

	CPBall *m_pBall;
	CPPaddle *m_pPaddles;

	uint8 m_MenuPos;
	uint8 m_State;
	uint8 m_Mode;
public:
	static const uint8 STATE_MENU=0;
	static const uint8 STATE_RUN=1;
	static const uint8 STATE_GAMEOVER=2;
	static const uint8 STATE_EXIT=3;

	static const uint8 MODE_1PLAYER=0;
	static const uint8 MODE_2PLAYER=1;

	uint8 GetMenuPos(){return(m_MenuPos);};
	void SetMenuPos(uint8 pos){m_MenuPos=pos;};
	uint8 GetMode(){return(m_Mode);};
	void SetMode(uint8 mode){m_Mode=mode;};
	uint8 GetState(){return(m_State);};
	void SetState(uint8 state){m_State=state;};
	CPDraw* GetDraw(){return(m_pDraw);};
	void SetDraw(CPDraw *draw){m_pDraw=draw;};
	CPlayers* GetPlayers(){return(m_pPlayers);};
	void SetPlayers(CPlayers *players){m_pPlayers=players;};

	CPBall* GetBall(){return(m_pBall);};
	void SetBall(CPBall *ball){m_pBall=ball;};

	void NewGame();
	void MovePaddleUp(uint8 player);
	void MovePaddleDown(uint8 player);

	CPGame(void);
	~CPGame(void);
};


#endif // __89FCC6E62458C847A92B21__P_GAME__HPP__
