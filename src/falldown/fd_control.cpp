#include "falldown/fd_control.hpp"

CFDControl::CFDControl(void)
{
}

CFDControl::~CFDControl(void)
{
}

void CFDControl::Respond(CFDGame *pGame,int player, CPlayers *pPlayers, unsigned long int frmctr)
{
	CDCControl *pControl=pPlayers->GetPlayer(player)->GetControl();
	if(!pControl->Init(frmctr))
		return;

	if(pGame->GetState()==CFDGame::STATE_MENU)
	{
		if((pControl->DDown(20))&&(pGame->GetMenuPos()<4))
		{
			pGame->SetMenuPos(pGame->GetMenuPos()+1);
		}
		else if((pControl->DUp(20))&&(pGame->GetMenuPos()>0))
		{
			pGame->SetMenuPos(pGame->GetMenuPos()-1);
		}
		else if(pControl->ADown())
		{
			if(pGame->GetMenuPos()==0)
			{
				pGame->SetMode(CFDGame::MODE_1PLAYER);
				pGame->SetState(CFDGame::STATE_RUN);
				pGame->NewGame();
			}
			else if((pGame->GetMenuPos()==1)&&(pPlayers->GetPlayers()>1))
			{
				pGame->SetMode(CFDGame::MODE_2PLAYER);
				pGame->SetState(CFDGame::STATE_RUN);
				pGame->NewGame();
			}
			else if((pGame->GetMenuPos()==2)&&(pPlayers->GetPlayers()>2))
			{
				pGame->SetMode(CFDGame::MODE_3PLAYER);
				pGame->SetState(CFDGame::STATE_RUN);
				pGame->NewGame();
			}
			else if((pGame->GetMenuPos()==3)&&(pPlayers->GetPlayers()>3))
			{
				pGame->SetMode(CFDGame::MODE_4PLAYER);
				pGame->SetState(CFDGame::STATE_RUN);
				pGame->NewGame();
			}
			else if(pGame->GetMenuPos()==4)
			{
				pGame->SetState(CFDGame::STATE_EXIT);
			}
		}
	}
	else if(pGame->GetState()==CFDGame::STATE_RUN)
	{
		if(pControl->DLeft(0))
		{
			pGame->MoveLeft(player);
		}
		else if(pControl->DRight(0))
		{
			pGame->MoveRight(player);
		}
		else if(pControl->StartDown())
		{
			pGame->SetState(CFDGame::STATE_PAUSE);
		}
	}
	else if(pGame->GetState()==CFDGame::STATE_PAUSE)
	{
		if((pControl->DDown(20))&&(pGame->GetPauseMenuPos()==0))
		{
			pGame->SetPauseMenuPos(1);
		}
		else if((pControl->DUp(20))&&(pGame->GetPauseMenuPos()==1))
		{
			pGame->SetPauseMenuPos(0);
		}
		else if(pControl->ADown())
		{
			if(pGame->GetPauseMenuPos()==0)
				pGame->SetState(CFDGame::STATE_RUN);
			else
				pGame->SetState(CFDGame::STATE_MENU);
			pGame->SetPauseMenuPos(0);
		}
	}
}
