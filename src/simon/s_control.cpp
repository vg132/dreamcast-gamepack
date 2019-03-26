#include "simon/s_control.hpp"

CSControl::CSControl(void)
{
}

CSControl::~CSControl(void)
{
}

void CSControl::Respond(CSGame *pGame, uint8 player, CPlayers *pPlayers, uint32 frmctr)
{
	CDCControl *pControl=pPlayers->GetPlayer(player)->GetControl();
	if(!pControl->Init(frmctr))
		return;

	if(pGame->GetState()==CSGame::STATE_MENU)
	{
		if((pControl->DDownDown())&&(pGame->GetMenuPos()<4))
		{
			pGame->SetMenuPos(pGame->GetMenuPos()+1);
		}
		if((pControl->DUpDown())&&(pGame->GetMenuPos()>0))
		{
			pGame->SetMenuPos(pGame->GetMenuPos()-1);
		}
		if(pControl->ADown())
		{
			pGame->SetState(CSGame::STATE_P1TURN);
			switch(pGame->GetMenuPos())
			{
				case 0:
					pGame->SetMode(CSGame::MODE_1PLAYER);
					break;
				case 1:
					pGame->SetMode(CSGame::MODE_2PLAYER);
					break;
				case 2:
					pGame->SetMode(CSGame::MODE_3PLAYER);
					break;
				case 3:
					pGame->SetMode(CSGame::MODE_4PLAYER);
					break;
				case 4:
					pGame->SetState(CSGame::STATE_EXIT);
					break;
			}
		}
	}
}
