#ifndef __F5E161BDD0A886FAA496C5__CONTROL__HPP__
#define __F5E161BDD0A886FAA496C5__CONTROL__HPP__

#include <kos.h>

#include "dccommon/dccontrol.hpp"
#include "dccommon/timer.hpp"
#include "main/game.hpp"
#include "falldown/falldown.hpp"
#include "minesweeper/minesweeper.hpp"
#include "starter/starter.hpp"
#include "simon/simon.hpp"
#include "pong/pong.hpp"
#include "main/draw.hpp"

class CControl
{
private:
	CTimer m_Timer;

	void ShowMem();
public:
	void Respond(CGame *pGame, CDCControl *pControl, unsigned long int frmctr);
	CControl();
	~CControl();
};

#endif // __F5E161BDD0A886FAA496C5__CONTROL__HPP__
