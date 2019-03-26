#ifndef __312D2975746ECD2758D7C__GAMEPACK__HPP__
#define __312D2975746ECD2758D7C__GAMEPACK__HPP__

#include <kos.h>
#include <time.h>

#include "main/draw.hpp"
#include "main/control.hpp"
#include "main/game.hpp"

class CGamePack
{
private:
	CControl *m_pControl;
	CDraw *m_pDraw;
	CGame *m_pGame;
public:
	void Start();
	CGamePack(void);
	~CGamePack(void);
};

#endif // __312D2975746ECD2758D7C__GAMEPACK__HPP__
