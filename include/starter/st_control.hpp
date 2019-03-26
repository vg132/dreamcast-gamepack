#ifndef __49D2DD689F0C76977F971__ST_CONTROL__HPP__
#define __49D2DD689F0C76977F971__ST_CONTROL__HPP__

#include <kos.h>

#include "dccommon/dccontrol.hpp"
#include "main/players.hpp"
#include "starter/st_game.hpp"
#include "starter/st_draw.hpp"

class CSTControl
{
private:
public:
	void Respond(CSTGame *pGame,uint8 player, CPlayers *pPlayers, uint32 frmctr);
	CSTControl(void);
	~CSTControl(void);
};


#endif // __49D2DD689F0C76977F971__ST_CONTROL__HPP__
