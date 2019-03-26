#include "falldown/fd_game.hpp"

CFDGame::CFDGame(CFDDraw *draw, CPlayers *players)
{
	srand(rtc_unix_secs());
	m_pField=NULL;
	m_pPlayers=players;
	m_pDraw=draw;
	m_iMenuPos=0;
	for(int i=0;i<4;i++)
		m_pBall[i]=NULL;
}

CFDGame::~CFDGame(void)
{
	if(m_pField!=NULL)
		delete m_pField;
	for(int i=0;i<4;i++)
	{
		if(m_pBall[i]!=NULL)
			delete m_pBall[i];
	}
}

void CFDGame::NewGame()
{
	if(m_pField!=NULL)
		delete m_pField;
	m_pField=new CFDField();

	for(int i=0;i<4;i++)
	{
		if(m_pBall[i]!=NULL)
		{
			delete m_pBall[i];
			m_pBall[i]=NULL;
		}
	}

	switch(GetMode())
	{
		case CFDGame::MODE_4PLAYER:
			m_pBall[3]=new CFDBall();
			m_pBall[3]->SetX(29);
			m_pBall[3]->SetPlayer(3);
			m_pPlayers->GetPlayer(3)->SetLives(1);
		case CFDGame::MODE_3PLAYER:
			m_pBall[2]=new CFDBall();
			m_pBall[2]->SetX(12);
			m_pBall[2]->SetPlayer(2);
			m_pPlayers->GetPlayer(2)->SetLives(1);
		case CFDGame::MODE_2PLAYER:
			m_pBall[1]=new CFDBall();
			m_pBall[1]->SetX(-12);
			m_pBall[1]->SetPlayer(1);
			m_pPlayers->GetPlayer(1)->SetLives(1);
		case CFDGame::MODE_1PLAYER:
			m_pBall[0]=new CFDBall();
			m_pBall[0]->SetX(-29);
			m_pBall[0]->SetPlayer(0);
			m_pPlayers->GetPlayer(0)->SetLives(1);
			break;
	}

	m_iBlockSpeed=350;
	m_iSpeed=0;
	m_iLevel=1;
	m_iPoints=0;
}

void CFDGame::Update()
{
	int i(0);
	if(GetState()==CFDGame::STATE_RUN)
	{
		//Move ball down
		for(i=0;i<4;i++)
		{
			if((m_pBall[i]!=NULL)&&(m_pPlayers->GetPlayer(i)->GetLives()>0))
			{
				float speed=m_pBall[i]->GetDropSpeed();
				float y=m_pBall[i]->GetY();
				m_pBall[i]->SetDropSpeed((float)(m_pBall[i]->GetDropSpeed()+m_pBall[i]->GetAcceleration()));
				m_pBall[i]->SetY(m_pBall[i]->GetY()-m_pBall[i]->GetDropSpeed());
				if(CheckCollision(m_pBall[i])!=NULL)
				{
					m_pBall[i]->SetDropSpeed(speed);
					m_pBall[i]->SetY(y);
					MoveLeft(i);
				}
				if(m_pBall[i]->GetY()<-38)
				{
					m_pBall[i]->SetY(-38);
				}
				else if(m_pBall[i]->GetY()>44)
				{
					m_pPlayers->GetPlayer(i)->SetLives(0);
					printf("Game Over Player %d\n",i);
				}
			}
		}

		//Move blocks down and ball up if its on top of the blocks
		for(i=0;i<6;i++)
		{
			for(int iLoop=0;iLoop<4;iLoop++)
			{
				if((m_pBall[iLoop]!=NULL)&&(m_pPlayers->GetPlayer(iLoop)->GetLives()>0))
				{
					if((m_pBall[iLoop]->GetY()<m_pField->GetRow(i)->i_Height/1000.0f+1.75)&&((m_pBall[iLoop]->GetY()+0.006f*100+(float)m_iBlockSpeed/1000.0f)>m_pField->GetRow(i)->i_Height/1000.0f+1.75f))
					{
						for(int j=0;j<=15;j++)
						{
							//check x coord only with active blocks
							if((m_pField->GetRow(i)->i_Blocks[j]==1)&&(m_pBall[iLoop]->GetX()<(m_pBall[iLoop]->GetSize()/13+(float)((-15.0f*m_pField->GetBlockWidth()/2+j*m_pField->GetBlockWidth()))+m_pField->GetBlockWidth()/2))&&(m_pBall[iLoop]->GetX()>(-m_pBall[iLoop]->GetSize()/13-1.5+(float)((-15.0f*m_pField->GetBlockWidth()/2+j*m_pField->GetBlockWidth()))-m_pField->GetBlockWidth()/2)))
							{
								float yMovement=m_pBall[iLoop]->GetY();
								m_pBall[iLoop]->SetY((float)m_pField->GetRow(i)->i_Height/1000+1.8f);
								yMovement=m_pBall[iLoop]->GetY()-yMovement;
								m_pBall[iLoop]->SetDropSpeed(0);

								CFDBall *ball=CheckCollision(m_pBall[iLoop]);
								if(ball!=NULL)
								{
									if(ball->GetY()>m_pBall[iLoop]->GetY())
									{
										ball->SetY(ball->GetY()+yMovement);
										ball->SetDropSpeed(0);
									}
								}
								break;
							}
						}
					}
				}
			}
		}

		//Only move field if there are any players still alive
		for(i=0;i<4;i++)
		{
			if((m_pBall[i]!=NULL)&&(m_pPlayers->GetPlayer(i)->GetLives()>0))
			{
				for(int iLoop=0;iLoop<6;iLoop++)
				{
					m_pField->GetRow(iLoop)->i_Height+=m_pField->GetBlockSpeed();
					if(m_pField->GetRow(iLoop)->i_Height>45000)
					{
						m_pField->GetRow(iLoop)->i_Height=-45000;
						m_pField->MakeBlock(iLoop);
						m_iPoints++;
					}
				}
				break;
			}
		}

		for(i=0;i<4;i++)
		{
			if((m_pBall[i]!=NULL)&&(m_pPlayers->GetPlayer(i)->GetLives()>0))
			{
				if(m_pBall[i]->GetX()<-47)
					m_pBall[i]->SetX(-47.0f);
				else if(m_pBall[i]->GetX()>45)
					m_pBall[i]->SetX(45.0f);
			}
		}
	}
}

CFDBall* CFDGame::CheckCollision(CFDBall *ball)
{
	for(int i=0;i<4;i++)
	{
		if((m_pBall[i]!=NULL)&&(m_pBall[i]!=ball)&&(m_pPlayers->GetPlayer(i)->GetLives()>0))
		{
			if(ball->Intersect(m_pBall[i]))
				return(m_pBall[i]);
		}
	}
	return(NULL);
}

void CFDGame::MoveLeft(uint8 player)
{
	float x=m_pBall[player]->GetX();
	int angle=m_pBall[player]->GetAngle();
  m_pBall[player]->SetX((float)m_pBall[player]->GetX()-(m_pBall[player]->GetSpeed()/1000.0f));
	m_pBall[player]->SetAngle(m_pBall[player]->GetAngle()+5);
	//If there is a collision, change back to old values
	if(CheckCollision(m_pBall[player])!=NULL)
	{
		m_pBall[player]->SetX(x);
		m_pBall[player]->SetAngle(angle);
	}
}

void CFDGame::MoveRight(uint8 player)
{
	float x=m_pBall[player]->GetX();
	int angle=m_pBall[player]->GetAngle();
	m_pBall[player]->SetX((float)m_pBall[player]->GetX()+(m_pBall[player]->GetSpeed()/1000.0f));
	m_pBall[player]->SetAngle(m_pBall[player]->GetAngle()-5);
	//If there is a collision, change back to old values
	if(CheckCollision(m_pBall[player])!=NULL)
	{
		m_pBall[player]->SetX(x);
		m_pBall[player]->SetAngle(angle);
	}
}
