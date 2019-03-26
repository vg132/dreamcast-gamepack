#ifndef __F836A9C5E5E07539AA9D32__FDCONTROL__HPP__
#define __F836A9C5E5E07539AA9D32__FDCONTROL__HPP__

#include "dccommon/dccontrol.hpp"
#include "falldown/fd_game.hpp"

class CFDControl
{
private:
public:
	void Respond(CFDGame *pGame,int player, CPlayers *pPlayers, unsigned long int frmctr);

	CFDControl(void);
	~CFDControl(void);
};

#endif // __F836A9C5E5E07539AA9D32__FDCONTROL__HPP__
