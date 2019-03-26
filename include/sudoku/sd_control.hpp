#ifndef __F5BB6B8A658747E17512__SD_CONTROL__HPP__
#define __F5BB6B8A658747E17512__SD_CONTROL__HPP__

#include "dccommon/dccontrol.hpp"
#include "sudoku/sd_game.hpp"
#include "sudoku/sd_draw.hpp"

class CSDControl
{
private:
public:
	void Respond(CMSGame *pGame,uint8 player, CPlayers *pPlayers, uint32 frmctr);
	CSDControl(void);
	~CSDControl(void);
};


#endif // __F5BB6B8A658747E17512__SD_CONTROL__HPP__
