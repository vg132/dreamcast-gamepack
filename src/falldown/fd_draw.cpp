#include "falldown/fd_draw.hpp"

CFDDraw::CFDDraw(void)
{
	f_ColorR[0]=1.0f;
	f_ColorR[1]=0.5f;
	f_ColorR[2]=0.5f;

	f_ColorG[0]=1.0f;
	f_ColorG[1]=0.5f;
	f_ColorG[2]=1.0f;

	f_ColorB[0]=1.0f;
	f_ColorB[1]=1.0f;
	f_ColorB[2]=0.5f;

	GLInit();
	LoadTextures();
}

CFDDraw::~CFDDraw(void)
{
	UnloadTextures();
}

static pvr_poly_cxt_t cxt;
static pvr_poly_hdr_t hdr;

static void sphere(float radius, int slices, int stacks, float rr, float gg, float bb)
{
	int	i, j;
	float	pitch, pitch2;
	float	x, y, z, g, b,r=0.0f;
	float	yaw, yaw2;
	pvr_vertex_t	*vert;
	pvr_dr_state_t	dr_state;

	pvr_dr_init(dr_state);

	glKosMatrixIdent();
	glKosMatrixApply(GL_KOS_SCREENVIEW);
	glKosMatrixApply(GL_PROJECTION);
	glKosMatrixApply(GL_MODELVIEW);

	pvr_prim(&hdr, sizeof(hdr));

	for(i=0;i<stacks;i++)
	{
		pitch = 2*M_PI * ( (float)i/(float)stacks );
		pitch2 = 2*M_PI * ( (float)(i+1)/(float)stacks );

		for ( j=0; j<=slices/2; j++ )
		{
			yaw = 2*M_PI * ( (float)j/(float)slices );
			yaw2 = 2*M_PI * ( (float)(j+1)/(float)slices );

			x = radius * fcos( yaw ) * fcos( pitch2 );
			y = radius * fsin( pitch2 );
			z = radius * fsin( yaw ) * fcos( pitch2 );
			mat_trans_single(x, y, z);
			g = fcos( yaw*2 ) / 2.0f + 0.5f;
			b = fsin( 0.0f + pitch2 ) / 2.0f + 0.5f;

			vert = pvr_dr_target(dr_state);
			vert->flags = PVR_CMD_VERTEX;
			vert->x = x;
			vert->y = y;
			vert->z = z;
			vert->u = 0.0f;
			vert->v = 0.0f;
			vert->argb = PVR_PACK_COLOR(0.0f, r+rr, g+gg, b+bb);

			vert->oargb = 0xff000000;
			pvr_dr_commit(vert);

			x = radius * fcos( yaw ) * fcos( pitch );
			y = radius * fsin( pitch );
			z = radius * fsin( yaw ) * fcos( pitch );
			mat_trans_single(x, y, z);
			g = fcos( yaw*2 ) / 2.0f + 0.5f;
			b = fsin( 0.0f + pitch ) / 2.0f + 0.5f;

			vert = pvr_dr_target(dr_state);
			if (j == (slices/2))
				vert->flags = PVR_CMD_VERTEX_EOL;
			else
				vert->flags = PVR_CMD_VERTEX;
			vert->x = x;
			vert->y = y;
			vert->z = z;
			vert->u = 0.0f;
			vert->v = 0.0f;
			vert->argb = PVR_PACK_COLOR(0.5f, r, g, b-1.0f);
			vert->oargb = 0xff000000;
			pvr_dr_commit(vert);
		}
	}
}

void CFDDraw::GLInit()
{
	pvr_poly_cxt_col(&cxt, PVR_LIST_OP_POLY);
	cxt.gen.culling = PVR_CULLING_NONE;
	pvr_poly_compile(&hdr, &cxt);
}

void CFDDraw::LoadTextures()
{
	LoadPcxTxrToVRAM("/cd/gp/falldown/grass.pcx",&m_GameTextures[0]);
	LoadPcxTxrToVRAM("/cd/gp/falldown/grassflat.pcx",&m_GameTextures[1]);

	LoadPngTxrToVRAM("/cd/gp/menu/1player.png",&m_MainMenuTextures[0],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/gp/menu/2players.png",&m_MainMenuTextures[1],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/gp/menu/3players.png",&m_MainMenuTextures[2],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/gp/menu/4players.png",&m_MainMenuTextures[3],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/gp/menu/exit.png",&m_MainMenuTextures[4],PNG_FULL_ALPHA);

	LoadPngTxrToVRAM("/cd/gp/menu/continue.png",&m_PauseMenuTextures[0],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/gp/menu/quit.png",&m_PauseMenuTextures[1],PNG_FULL_ALPHA);

	LoadPngTxrToVRAM("/cd/gp/menu/falldownmenu.png",&m_BackgroundTextures[0]);
	LoadPngTxrToVRAM("/cd/gp/menu/pause.png",&m_BackgroundTextures[1],PNG_FULL_ALPHA);

	LoadPngTxrToVRAM("/cd/gp/menu/leftarrow.png",&m_ArrowTexture,PNG_FULL_ALPHA);
}

void CFDDraw::UnloadTextures()
{
	int i(0);

	for(i=0;i<2;i++)
	{
		glDeleteTextures(1,&m_GameTextures[i]);
		glDeleteTextures(1,&m_BackgroundTextures[i]);
		glDeleteTextures(1,&m_PauseMenuTextures[i]);
	}
	for(i=0;i<5;i++)
		glDeleteTextures(1,&m_MainMenuTextures[i]);
	glDeleteTextures(1,&m_ArrowTexture);
}

void CFDDraw::DrawBorder()
{
	int levelValue=m_pGame->GetLevel()-1;
	if(levelValue>2)
		levelValue=2;
	glDisable(GL_TEXTURE_2D);//shut of 2d textureing otherwise non textured items dont draw
	glDisable(GL_BLEND);//shut off blending or things will be transparent

	glColor3f(f_ColorR[levelValue],f_ColorG[levelValue],f_ColorB[levelValue]);

	glBegin(GL_QUADS);//Draw the walls with gradients between levelcolor and grey

		glColor3f(f_ColorR[levelValue],f_ColorG[levelValue],f_ColorB[levelValue]);

		glVertex3f(-47.0f,45.0f,1.0f);
		glVertex3f(-48.0f,45.0f,1.0f);
		glVertex3f(-48.0f,-40.0f,1.0f);
		glVertex3f(-47.0f,-40.0f,1.0f);

		glVertex3f(47.0f,45.0f,1.0f);
		glVertex3f(48.0f,45.0f,1.0f);
		glVertex3f(48.0f,-40.0f,1.0f);
		glVertex3f(47.0f,-40.0f,1.0f);
		glVertex3f(-47.0f,45.0f,1.0f);
		
		glColor3f(0.2f,0.2f,0.2f);
		glVertex3f(-47.0f,45.0f,-10.0f);
		glVertex3f(-47.0f,-40.0f,-10.0f);

		glColor3f(f_ColorR[levelValue],f_ColorG[levelValue],f_ColorB[levelValue]);

		glVertex3f(-47.0f,-40.0f,1.0f);
		glVertex3f(47.0f,45.0f,1.0f);

		glColor3f(0.2f,0.2f,0.2f);
		glVertex3f(47.0f,45.0f,-10.0f);
		glVertex3f(47.0f,-40.0f,-10.0f);

		glColor3f(f_ColorR[levelValue],f_ColorG[levelValue],f_ColorB[levelValue]);

		glVertex3f(47.0f,-40.0f,1.0f);
		glVertex3f(47.0f,-40.0f,1.0f);

		glColor3f(0.2f,0.2f,0.2f);
		glVertex3f(47.0f,-40.0f,-10.0f);
		glVertex3f(-47.0f,-40.0f,-10.0f);

		glColor3f(f_ColorR[levelValue],f_ColorG[levelValue],f_ColorB[levelValue]);

		glVertex3f(-47.0f,-40.0f,1.0f);

		glVertex3f(48.0f,-40.0f,1.0f);
		glVertex3f(48.0f,-50.0f,1.0f);
		glVertex3f(-48.0f,-50.0f,1.0f);
		glVertex3f(-48.0f,-40.0f,1.0f);

	glEnd();//probably should shorten this somehow
}


void CFDDraw::DrawScene(CFDGame *game)
{
	m_pGame=game;
	glKosBeginFrame();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	if(m_pGame->GetState()==CFDGame::STATE_MENU)
	{
		DrawMenu(m_ArrowTexture,m_BackgroundTextures[0],m_MainMenuTextures,5,m_pGame->GetMenuPos());
	}
	else if(m_pGame->GetState()==CFDGame::STATE_RUN)
	{
		glTranslatef(0.0f,0.0f,-100.0f);
		glRotatef(25,1.0f,0.0f,0.0f);
		DrawBorder();
		if(m_pGame->GetState()==CFDGame::STATE_RUN)
		{
			DrawField();
			switch(m_pGame->GetMode())
			{
				case CFDGame::MODE_4PLAYER:
					DrawBall(3);
				case CFDGame::MODE_3PLAYER:
					DrawBall(2);
				case CFDGame::MODE_2PLAYER:
					DrawBall(1);
				case CFDGame::MODE_1PLAYER:
					DrawBall(0);
					break;
			}
		}
		glLoadIdentity();
		//TexturedRect(m_iMenuTextures[2],196.0f,60.0f,256.0f,256.0f);
		//m_Print.Print(150,150,1.0f,0.0f,0.0f,"Points 123");
	}
	else if(m_pGame->GetState()==CFDGame::STATE_PAUSE)
	{
		DrawMenu(m_ArrowTexture,m_BackgroundTextures[1],m_PauseMenuTextures,2,m_pGame->GetPauseMenuPos());
	}
	else if(m_pGame->GetState()==CFDGame::STATE_GAMEOVER)
	{
		
	}
	glKosFinishFrame();
}

void CFDDraw::DrawBall(int id)
{
	glTranslatef((float)m_pGame->GetBall(id)->GetX()+1.0f,m_pGame->GetBall(id)->GetY()+0.5f,-5.0f);
	//glRotatef(m_pGame->GetBall(id)->GetAngle(), 0.75f, 1.0f, 0.5f);

	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	sphere(2.0f, 20, 20,m_pGame->GetBall(id)->GetRed(),m_pGame->GetBall(id)->GetGreen(),m_pGame->GetBall(id)->GetBlue());
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);

	//glRotatef(-m_pGame->GetBall(id)->GetAngle(), 0.75f, 1.0f, 0.5f);
	glTranslatef(-(float)m_pGame->GetBall(id)->GetX()+1.0f,-m_pGame->GetBall(id)->GetY()-0.5f,+5.0f);
}

void CFDDraw::DrawField()
{
	BlockSet_t *Block;
	for(int row=0;row<6;row++)
	{
		Block=m_pGame->GetField()->GetRow(row);
		for(int i=0;i<16;i++)
		{
			glDisable(GL_BLEND);
			glEnable(GL_TEXTURE_2D);
			if(Block->i_Blocks[i]==1)
			{
				glBindTexture(GL_TEXTURE_2D, m_GameTextures[0]);

				//Front wall
				glBegin(GL_QUADS);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f((float)((-15.0f*m_pGame->GetField()->GetBlockWidth()/2+i*m_pGame->GetField()->GetBlockWidth()))-m_pGame->GetField()->GetBlockWidth()/2,(float)Block->i_Height/1000,0.0f);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f((float)((-15.0f*m_pGame->GetField()->GetBlockWidth()/2+i*m_pGame->GetField()->GetBlockWidth()))+m_pGame->GetField()->GetBlockWidth()/2,(float)Block->i_Height/1000,0.0f);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f((float)((-15.0f*m_pGame->GetField()->GetBlockWidth()/2+i*m_pGame->GetField()->GetBlockWidth()))+m_pGame->GetField()->GetBlockWidth()/2,(float)Block->i_Height/1000-2.0f,0.0f);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f((float)((-15.0f*m_pGame->GetField()->GetBlockWidth()/2+i*m_pGame->GetField()->GetBlockWidth()))-m_pGame->GetField()->GetBlockWidth()/2,(float)Block->i_Height/1000-2.0f,0.0f);
				glEnd();

				glBindTexture(GL_TEXTURE_2D, m_GameTextures[1]);

				glBegin(GL_QUADS);
				
					//Top section
					glTexCoord2f(1.0f,1.0f);
					glVertex3f((float)((-15.0f*m_pGame->GetField()->GetBlockWidth()/2+i*m_pGame->GetField()->GetBlockWidth()))-m_pGame->GetField()->GetBlockWidth()/2,(float)Block->i_Height/1000,0.0f);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f((float)((-15.0f*m_pGame->GetField()->GetBlockWidth()/2+i*m_pGame->GetField()->GetBlockWidth()))+m_pGame->GetField()->GetBlockWidth()/2,(float)Block->i_Height/1000,0.0f);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f((float)((-15.0f*m_pGame->GetField()->GetBlockWidth()/2+i*m_pGame->GetField()->GetBlockWidth()))+m_pGame->GetField()->GetBlockWidth()/2,(float)Block->i_Height/1000,-10.0f);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f((float)((-15.0f*m_pGame->GetField()->GetBlockWidth()/2+i*m_pGame->GetField()->GetBlockWidth()))-m_pGame->GetField()->GetBlockWidth()/2,(float)Block->i_Height/1000,-10.0f);

					//Bottom section
					glTexCoord2f(1.0f,1.0f);
					glVertex3f((float)((-15.0f*m_pGame->GetField()->GetBlockWidth()/2+i*m_pGame->GetField()->GetBlockWidth()))-m_pGame->GetField()->GetBlockWidth()/2,(float)Block->i_Height/1000-2.0f,0.0f);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f((float)((-15.0f*m_pGame->GetField()->GetBlockWidth()/2+i*m_pGame->GetField()->GetBlockWidth()))+m_pGame->GetField()->GetBlockWidth()/2,(float)Block->i_Height/1000-2.0f,0.0f);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f((float)((-15.0f*m_pGame->GetField()->GetBlockWidth()/2+i*m_pGame->GetField()->GetBlockWidth()))+m_pGame->GetField()->GetBlockWidth()/2,(float)Block->i_Height/1000-2.0f,-10.0f);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f((float)((-15.0f*m_pGame->GetField()->GetBlockWidth()/2+i*m_pGame->GetField()->GetBlockWidth()))-m_pGame->GetField()->GetBlockWidth()/2,(float)Block->i_Height/1000-2.0f,-10.0f);

					//Right wall
					glTexCoord2f(1.0f,1.0f);
					glVertex3f((float)((-15.0f*m_pGame->GetField()->GetBlockWidth()/2+i*m_pGame->GetField()->GetBlockWidth()))+m_pGame->GetField()->GetBlockWidth()/2,(float)Block->i_Height/1000,0.0f);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f((float)((-15.0f*m_pGame->GetField()->GetBlockWidth()/2+i*m_pGame->GetField()->GetBlockWidth()))+m_pGame->GetField()->GetBlockWidth()/2,(float)Block->i_Height/1000-2,0.0f);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f((float)((-15.0f*m_pGame->GetField()->GetBlockWidth()/2+i*m_pGame->GetField()->GetBlockWidth()))+m_pGame->GetField()->GetBlockWidth()/2,(float)Block->i_Height/1000-2,-10.0f);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f((float)((-15.0f*m_pGame->GetField()->GetBlockWidth()/2+i*m_pGame->GetField()->GetBlockWidth()))+m_pGame->GetField()->GetBlockWidth()/2,(float)Block->i_Height/1000,-10.0f);
					
					//Left wall
					glTexCoord2f(1.0f,1.0f);
					glVertex3f((float)((-15.0f*m_pGame->GetField()->GetBlockWidth()/2+i*m_pGame->GetField()->GetBlockWidth()))-m_pGame->GetField()->GetBlockWidth()/2,(float)Block->i_Height/1000,0.0f);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f((float)((-15.0f*m_pGame->GetField()->GetBlockWidth()/2+i*m_pGame->GetField()->GetBlockWidth()))-m_pGame->GetField()->GetBlockWidth()/2,(float)Block->i_Height/1000-2,0.0f);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f((float)((-15.0f*m_pGame->GetField()->GetBlockWidth()/2+i*m_pGame->GetField()->GetBlockWidth()))-m_pGame->GetField()->GetBlockWidth()/2,(float)Block->i_Height/1000-2,-10.0f);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f((float)((-15.0f*m_pGame->GetField()->GetBlockWidth()/2+i*m_pGame->GetField()->GetBlockWidth()))-m_pGame->GetField()->GetBlockWidth()/2,(float)Block->i_Height/1000,-10.0f);
				glEnd();
			}
			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
		}
	}
}
