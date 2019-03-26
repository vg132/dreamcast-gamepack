#include "sudoku/sd_control.hpp"

CSDControl::CSDControl(void)
{
}

CSDControl::~CSDControl(void)
{
}

void CMSControl::Respond(CSDGame *pGame, uint8 player, CPlayers *pPlayers, uint32 frmctr)
{
	CDCControl *pControl=pPlayers->GetPlayer(player)->GetControl();
	if(!pControl->Init(frmctr))
		return;
	if(pGame->GetState()==CSDGame::STATE_MENU)
	{
		if((pControl->DDown(20))&&(pGame->GetMenuPos()<3))
		{
			pGame->SetMenuPos(pGame->GetMenuPos()+1);
		}
		else if((pControl->DUp(20))&&(pGame->GetMenuPos()>0))
		{
			pGame->SetMenuPos(pGame->GetMenuPos()-1);
		}
		else if(pControl->ADown())
		{
			if(pGame->GetMenuPos()<3)
			{
				pGame->NewGame(pGame->GetMenuPos());
				pGame->GetDraw()->ResetView();
				pGame->SetState(CSDGame::STATE_RUN);
			}
			else if(pGame->GetMenuPos()==3)
			{
				pGame->SetState(CSDGame::STATE_EXIT);
			}
		}
	}
	else if(pGame->GetState()==CSDGame::STATE_RUN)
	{
		if(pControl->YDown())
			pGame->SetState(CSDGame::STATE_MENU);
		if(pControl->BDown())
			pGame->GetDraw()->ResetView();
/*		if(pControl->ADown())
			pGame->Open();
		if(pControl->XDown())
			pGame->Mark();*/
		if(pControl->DLeft(8))
			pGame->MoveLeft();
		if(pControl->DRight(8))
			pGame->MoveRight();
		if(pControl->DUp(8))
			pGame->MoveUp();
		if(pControl->DDown(8))
			pGame->MoveDown();
		if(pControl->GetLeftTrigger()>0)
			pGame->GetDraw()->SetZoom(pGame->GetDraw()->GetZoom()+(float)(pControl->GetLeftTrigger()/255.0f));
		if(pControl->GetRightTrigger()>0)
			pGame->GetDraw()->SetZoom(pGame->GetDraw()->GetZoom()-(float)(pControl->GetRightTrigger()/255.0f));			
		if(pControl->GetJoy1X()<128)
			pGame->GetDraw()->SetYRot(pGame->GetDraw()->GetYRot()-(float)((128-pControl->GetJoy1X())/100.0f));
		else if(pControl->GetJoy1X()>128)
			pGame->GetDraw()->SetYRot(pGame->GetDraw()->GetYRot()+(float)((pControl->GetJoy1X()-128)/100.0f));
		if(pControl->GetJoy1Y()<128)
			pGame->GetDraw()->SetXRot(pGame->GetDraw()->GetXRot()-(float)((128-pControl->GetJoy1Y())/100.0f));
		else if(pControl->GetJoy1Y()>128)
			pGame->GetDraw()->SetXRot(pGame->GetDraw()->GetXRot()+(float)((pControl->GetJoy1Y()-128)/100.0f));
	}
	else if((pGame->GetState()==CSDGame::STATE_GAMEOVER)||(pGame->GetState()==CSDGame::STATE_WON))
	{
		if(pControl->YDown())
			pGame->SetState(CSDGame::STATE_MENU);
	}
}
