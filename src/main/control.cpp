#include "main/control.hpp"

CControl::CControl(void)
{
}

CControl::~CControl(void)
{
}

void CControl::Respond(CGame *pGame, CDCControl *pControl, unsigned long int frmctr)
{
	if(!pControl->Init(frmctr))
		return;
#ifdef __DEBUG__

	if(pControl->YDown())
	{
		m_Timer.Reset();
	}
	if(pControl->XDown())
	{
		printf("Time: %s\n",m_Timer.GetTimeString());
		/*printf("XX: %f\n",pGame->GetDraw()->xx);
		printf("YY: %f\n",pGame->GetDraw()->yy);*/
		printf("Menu Pos: %d\n",pGame->GetMenuPos());
	}
	if(pControl->ADown())
	{
		if(!m_Timer.IsRunning())
			m_Timer.Start();
		else
			m_Timer.Pause();
	}
	if(pControl->BDown())
	{
		m_Timer.Stop();
	}

#endif
	if((pControl->DLeft(20))&&(((pGame->GetMenuPos())%2)!=0))
	{
		pGame->SetMenuPos(pGame->GetMenuPos()-1);
	}
	else if((pControl->DRight(20))&&(((pGame->GetMenuPos())%2)==0))
	{
		pGame->SetMenuPos(pGame->GetMenuPos()+1);
	}
	else if((pControl->DUp(20))&&(pGame->GetMenuPos()>1))
	{
		pGame->SetMenuPos(pGame->GetMenuPos()-2);
	}
	else if((pControl->DDown(20))&&(pGame->GetMenuPos()<8))
	{
		pGame->SetMenuPos(pGame->GetMenuPos()+2);
	}
#ifdef __DEBUG__
	else if(pControl->YDown())
	{
		pGame->SetState(CGame::STATE_EXIT);
	}
#endif
	else if(pControl->StartDown())
	{
		pGame->GetDraw()->UnloadMainTextures();
#ifdef __DEBUG__
		ShowMem();
#endif
		if(pGame->GetMenuPos()==0)
		{
			CFallDown *falldown=new CFallDown();
			falldown->Start(pGame->GetPlayers());
			delete falldown;
		}
		else if(pGame->GetMenuPos()==1)
		{
			/*
			CSnake *snake=new CSnake();
			snake->Start(pGame->GetPlayers());
			delete snake;
			*/
		}
		else if(pGame->GetMenuPos()==2)
		{
			CSimon *simon=new CSimon();
			simon->Start(pGame->GetPlayers());
			delete simon;
		}
		else if(pGame->GetMenuPos()==3)
		{
			/*
			CTetris *tetris=new CTetris();
			tetris->Start(pGame->GetPlayers());
			delete tetris;
			*/
		}
		else if(pGame->GetMenuPos()==4)
		{
			CPong *pong=new CPong();
			pong->Start(pGame->GetPlayers());
			delete pong;
		}
		else if(pGame->GetMenuPos()==5)
		{
			CStarter *starter=new CStarter();
			starter->Start(pGame->GetPlayers());
			delete starter;
		}
		else if(pGame->GetMenuPos()==6)
		{
			CMinesweeper *ms=new CMinesweeper();
			ms->Start(pGame->GetPlayers());
			delete ms;
		}
#ifdef __DEBUG__
		ShowMem();
#endif
		pGame->GetDraw()->LoadMainTextures();
	}
}

void CControl::ShowMem()
{
	printf("-------------Main Memory------------\n");
	malloc_stats();
	printf("-------------PVR Memory-------------\n");
	pvr_mem_stats();
	printf("------------------------------------\n");
}
