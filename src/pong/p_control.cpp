#include "pong/p_control.hpp"

CPControl::CPControl(void)
{
}

CPControl::~CPControl(void)
{
}

void CPControl::Respond(CPGame *pGame, uint8 player, CPlayers *pPlayers, uint32 frmctr)
{
	CDCControl *pControl=pPlayers->GetPlayer(player)->GetControl();
	if(!pControl->Init(frmctr))
		return;

	if(pGame->GetState()==CPGame::STATE_MENU)
	{
		if((pControl->DDownDown())&&(pGame->GetMenuPos()<2))
		{
			pGame->SetMenuPos(pGame->GetMenuPos()+1);
		}
		if((pControl->DUpDown())&&(pGame->GetMenuPos()>0))
		{
			pGame->SetMenuPos(pGame->GetMenuPos()-1);
		}
		if(pControl->ADown())
		{
			switch(pGame->GetMenuPos())
			{
				case 0:
					pGame->SetMode(CPGame::MODE_1PLAYER);
					pGame->SetState(CPGame::STATE_RUN);
					pGame->NewGame();
					break;
				case 1:
					pGame->SetMode(CPGame::MODE_2PLAYER);
					pGame->SetState(CPGame::STATE_RUN);
					pGame->NewGame();
					break;
				case 2:
					pGame->SetState(CPGame::STATE_EXIT);
					break;
			}
		}
	}
	else if(pGame->GetState()==CPGame::STATE_RUN)
	{
		if(pControl->ADown())
			pGame->SetState(CPGame::STATE_MENU);
		if(pControl->BDown())
			pGame->GetBall()->Move();
	}
}
