#include "starter/st_control.hpp"

CSTControl::CSTControl(void)
{
}

CSTControl::~CSTControl(void)
{
}

void CSTControl::Respond(CSTGame *pGame, uint8 player, CPlayers *pPlayers, uint32 frmctr)
{
	CDCControl *pControl=pPlayers->GetPlayer(player)->GetControl();
	if(!pControl->Init(frmctr))
		return;
/*

	if(player==1)
	{
		if(pControl->ADown())
			printf("XX: %d, YY: %d\n",pGame->GetDraw()->xx,pGame->GetDraw()->yy);
		if(pControl->DLeft(7))
			pGame->GetDraw()->xx=pGame->GetDraw()->xx-1;
		if(pControl->DRight(7))
			pGame->GetDraw()->xx=pGame->GetDraw()->xx+1;
		if(pControl->DUp(7))
			pGame->GetDraw()->yy=pGame->GetDraw()->yy-1;
		if(pControl->DDown(7))
			pGame->GetDraw()->yy=pGame->GetDraw()->yy+1;
		return;
	}*/
	if(pGame->GetState()==CSTGame::STATE_MENU)
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
			if(pGame->GetMenuPos()==0)
				pGame->NewGame(1);
			else if((pGame->GetMenuPos()==1)&&(pPlayers->GetPlayers()>1))
				pGame->NewGame(2);
			else if((pGame->GetMenuPos()==2)&&(pPlayers->GetPlayers()>2))
				pGame->NewGame(3);
			else if((pGame->GetMenuPos()==3)&&(pPlayers->GetPlayers()>3))
				pGame->NewGame(4);
			else if(pGame->GetMenuPos()==4)
				pGame->SetState(CSTGame::STATE_EXIT);
		}
	}
	else if((pGame->GetState()==CSTGame::STATE_LIGHTS)||(pGame->GetState()==CSTGame::STATE_START))
	{
		if((pControl->XDown())||(pControl->ADown())||(pControl->YDown())||(pControl->BDown()))
			pGame->Stopped((uint8)(player));
	}
	else if(pGame->GetState()==CSTGame::STATE_GAMEOVER)
	{
		if((pControl->XDown())||(pControl->ADown())||(pControl->YDown())||(pControl->BDown())||(pControl->StartDown()))
			pGame->SetState(CSTGame::STATE_MENU);
	}
}
