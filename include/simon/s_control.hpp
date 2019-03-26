#ifndef __F774CBF8BB2FB91D83C613__S_CONTROL__HPP__
#define __F774CBF8BB2FB91D83C613__S_CONTROL__HPP__

#include <kos.h>

#include "dccommon/dccontrol.hpp"
#include "main/players.hpp"
#include "simon/s_game.hpp"
#include "simon/s_draw.hpp"

class CSControl
{
private:
public:
	void Respond(CSGame *pGame,uint8 player, CPlayers *pPlayers, uint32 frmctr);
	CSControl(void);
	~CSControl(void);
};


#endif // __F774CBF8BB2FB91D83C613__S_CONTROL__HPP__
