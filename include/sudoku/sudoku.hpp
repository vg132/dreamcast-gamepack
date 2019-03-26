#ifndef __3982E883260ECCF5A24C__SUDOKU__HPP__
#define __3982E883260ECCF5A24C__SUDOKU__HPP__

#include <kos.h>

#include "main/players.hpp"
#include "sudoku/sd_control.hpp"
#include "sudoku/sd_draw.hpp"
#include "sudoku/sd_game.hpp"

class CSudoku
{
private:
	CSDDraw *m_pDraw;
	CSDGame *m_pGame;
	CSDControl *m_pControl;

	void Run();
public:
	void Start(CPlayers *players);

	CSudoku(void);
	~CSudoku(void);
};


#endif // __3982E883260ECCF5A24C__SUDOKU__HPP__
