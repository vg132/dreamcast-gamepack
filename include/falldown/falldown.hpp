#ifndef __CD362DC4BCD7E7CAC474__FALLDOWN__HPP__
#define __CD362DC4BCD7E7CAC474__FALLDOWN__HPP__

#include <kos.h>

#include "falldown/fd_draw.hpp"
#include "falldown/fd_game.hpp"
#include "falldown/fd_control.hpp"
#include "main/players.hpp"

class CFallDown
{
private:
	CFDDraw *m_pDraw;
	CFDGame *m_pGame;
	CFDControl *m_pControl;

	void Run();
public:
	void Start(CPlayers *players);

	CFallDown(void);
	~CFallDown(void);
};

#endif // __CD362DC4BCD7E7CAC474__FALLDOWN__HPP__
