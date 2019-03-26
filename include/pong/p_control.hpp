#ifndef __383F05030A5A1FE8914D8__P_CONTROL__HPP__
#define __383F05030A5A1FE8914D8__P_CONTROL__HPP__

#include <kos.h>

#include "dccommon/dccontrol.hpp"
#include "main/players.hpp"
#include "pong/p_game.hpp"
#include "pong/p_draw.hpp"

class CPControl
{
private:
public:
	void Respond(CPGame *pGame,uint8 player, CPlayers *pPlayers, uint32 frmctr);

	CPControl(void);
	~CPControl(void);
};


#endif // __383F05030A5A1FE8914D8__P_CONTROL__HPP__
