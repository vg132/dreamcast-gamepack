#ifndef __C9BDAFA4D691E2288221DB__MINESWEEPER__H__
#define __C9BDAFA4D691E2288221DB__MINESWEEPER__H__

#include <kos.h>

#include "main/players.hpp"
#include "minesweeper/ms_control.hpp"
#include "minesweeper/ms_draw.hpp"
#include "minesweeper/ms_game.hpp"

class CMinesweeper
{
private:
	CMSDraw *m_pDraw;
	CMSGame *m_pGame;
	CMSControl *m_pControl;

	void Run();
public:
	void Start(CPlayers *players);

	CMinesweeper(void);
	~CMinesweeper(void);
};

#endif // __C9BDAFA4D691E2288221DB__MINESWEEPER__H__
