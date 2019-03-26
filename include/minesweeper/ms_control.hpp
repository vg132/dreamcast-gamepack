#ifndef __7BA66238DFBE34099A22__MS_CONTROL__HPP__
#define __7BA66238DFBE34099A22__MS_CONTROL__HPP__

#include "dccommon/dccontrol.hpp"
#include "minesweeper/ms_game.hpp"
#include "minesweeper/ms_draw.hpp"

class CMSControl
{
private:
public:
	void Respond(CMSGame *pGame,uint8 player, CPlayers *pPlayers, uint32 frmctr);
	CMSControl(void);
	~CMSControl(void);
};


#endif // __7BA66238DFBE34099A22__MS_CONTROL__HPP__
