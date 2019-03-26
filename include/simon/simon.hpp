#ifndef __5B394C4C829A99FC4BCCAC__SIMON__HPP__
#define __5B394C4C829A99FC4BCCAC__SIMON__HPP__

#include <kos.h>

#include "main/players.hpp"

#include "simon/s_draw.hpp"
#include "simon/s_game.hpp"
#include "simon/s_control.hpp"

class CSimon
{
private:
	CSControl *m_pControl;
	CSGame *m_pGame;
	CSDraw *m_pDraw;

	void Run();
public:
	void Start(CPlayers *players);
	CSimon(void);
	~CSimon(void);
};

#endif // __5B394C4C829A99FC4BCCAC__SIMON__HPP__
