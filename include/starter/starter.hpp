#ifndef __CF242B9458E555BC2D36E__STARTER__HPP__
#define __CF242B9458E555BC2D36E__STARTER__HPP__

#include <kos.h>

#include "main/players.hpp"
#include "starter/st_game.hpp"
#include "starter/st_draw.hpp"
#include "starter/st_control.hpp"

class CStarter
{
private:
	CSTGame *m_pGame;
	CSTControl *m_pControl;
	CSTDraw *m_pDraw;

	void Run();
public:
	void Start(CPlayers *players);
	CStarter(void);
	~CStarter(void);
};


#endif // __CF242B9458E555BC2D36E__STARTER__HPP__
