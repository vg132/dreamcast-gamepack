#include "pong/p_draw.hpp"

static pvr_poly_cxt_t cxt;
static pvr_poly_hdr_t hdr;

CPDraw::CPDraw(void)
{
	m_pPrint=new CPlPrint();
	m_pPrint->SetFont("/cd/gp/font/helvetica_medium.txf");

	LoadTextures();
	glKosInit();
	SetPerspective();

	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_FILTER, GL_FILTER_BILINEAR);

	pvr_poly_cxt_col(&cxt, PVR_LIST_OP_POLY);
	cxt.gen.culling = PVR_CULLING_NONE;
	pvr_poly_compile(&hdr, &cxt);
}

CPDraw::~CPDraw(void)
{
	UnloadTextures();
	delete m_pPrint;
}

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

void CPDraw::LoadTextures()
{
	LoadPngTxrToVRAM("/cd/gp/menu/1player.png",&m_MainMenuTextures[0],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/gp/menu/2players.png",&m_MainMenuTextures[1],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/gp/menu/exit.png",&m_MainMenuTextures[2],PNG_FULL_ALPHA);

	LoadPngTxrToVRAM("/rd/pong/paddle.png",&m_GameTextures[0],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/rd/pong/ball.png",&m_GameTextures[1],PNG_FULL_ALPHA);

	LoadPngTxrToVRAM("/cd/gp/menu/pongmenu.png",&m_BackgroundTexture);
	LoadPngTxrToVRAM("/cd/gp/menu/leftarrow.png",&m_ArrowTexture,PNG_FULL_ALPHA);
}

void CPDraw::UnloadTextures()
{
	uint8 i;
	for(i=0;i<3;i++)
		glDeleteTextures(1,&m_MainMenuTextures[i]);
	glDeleteTextures(1,&m_ArrowTexture);
	glDeleteTextures(1,&m_BackgroundTexture);
}

void CPDraw::DrawScene(CPGame *game)
{
	m_pGame=game;
	m_ListFinished=false;
	glKosBeginFrame();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	if(m_pGame->GetState()==CPGame::STATE_MENU)
	{
		DrawMenu(m_ArrowTexture,m_BackgroundTexture,m_MainMenuTextures,3,m_pGame->GetMenuPos(),0);
	}
	else if(m_pGame->GetState()==CPGame::STATE_RUN)
	{
		glTranslatef(0.0f,5.0f,-100.0f);
		DrawBorder(92.0f,60.0f,-0.5f);
		DrawBall(game->GetBall());
		glLoadIdentity();
	}
	glKosFinishFrame();
}



void CPDraw::DrawBorder(float width, float height, float depth)
{
	glDisable(GL_TEXTURE_2D);//shut of 2d textureing otherwise non textured items dont draw
	glDisable(GL_BLEND);//shut off blending or things will be transparent

	glColor3f(1.0f,1.0f,1.0f);

	glBegin(GL_QUADS);
		//Bottom
		glVertex3f((0-(width/2)),(0-(height/2)),0.0f);
		glVertex3f(width/2,(0-(height/2)),0.0f);
		glVertex3f(width/2,(0-(height/2)),depth);
		glVertex3f((0-(width/2)),(0-(height/2)),depth);

		//Left side
		glVertex3f((0-(width/2)),height/2,0.0f);
		glVertex3f((0-(width/2)),(0-(height/2)),0.0f);
		glVertex3f((0-(width/2)),(0-(height/2)),depth);
		glVertex3f((0-(width/2)),height/2,depth);

		//Right side
		glVertex3f(width/2,height/2,0.0f);
		glVertex3f(width/2,(0-(height/2)),0.0f);
		glVertex3f(width/2,(0-(height/2)),depth);
		glVertex3f(width/2,height/2,depth);

		//Top
		glVertex3f((0-(width/2)),height/2,0.0f);
		glVertex3f(width/2,height/2,0.0f);
		glVertex3f(width/2,height/2,depth);
		glVertex3f((0-(width/2)),height/2,depth);
	glEnd();
	glEnable(GL_TEXTURE_2D);
}

void CPDraw::DrawBall(CPBall *ball)
{
	glTranslatef(ball->GetRect()->GetX()+(ball->GetRect()->GetWidth()/2),ball->GetRect()->GetY()+(ball->GetRect()->GetHeight()/2),0.0f);
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	sphere(2.0f,20,20,1.0f,0.0f,0.0f);
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
	glTranslatef(-ball->GetRect()->GetX()+(ball->GetRect()->GetWidth()/2),-ball->GetRect()->GetY()+(ball->GetRect()->GetHeight()/2),0.0f);
}
