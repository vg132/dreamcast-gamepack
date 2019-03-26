#ifndef __1DC4FBE40B2C2C11EA20__PONG__HPP__
#define __1DC4FBE40B2C2C11EA20__PONG__HPP__

#include <kos.h>

#include "main/players.hpp"

#include "pong/p_draw.hpp"
#include "pong/p_game.hpp"
#include "pong/p_control.hpp"

class CPong
{
private:
	CPDraw *m_pDraw;
	CPGame *m_pGame;
	CPControl *m_pControl;

	void Run();
public:
	void Start(CPlayers *players);
	CPong(void);
	~CPong(void);
};

#endif // __1DC4FBE40B2C2C11EA20__PONG__HPP__
