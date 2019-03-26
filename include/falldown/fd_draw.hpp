#ifndef __391072E335AAC88281F9BA__DRAW__HPP__
#define __391072E335AAC88281F9BA__DRAW__HPP__

#include <math.h>
#include <kos.h>
#include <time.h>

#include "dccommon/gldraw.hpp"
#include "dccommon/plprint.hpp"
#include "main/gp_draw.hpp"

#include "fd_draw.hpp"
#include "fd_field.hpp"
#include "fd_game.hpp"
#include "fd_ball.hpp"

class CFDDraw : public CGPDraw
{
private:
	float f_ColorR[3];
	float f_ColorG[3];
	float f_ColorB[3];

	GLuint m_ArrowTexture;
	GLuint m_BackgroundTextures[2];
	GLuint m_MainMenuTextures[5];
	GLuint m_PauseMenuTextures[2];
	GLuint m_GameTextures[2];

	CFDGame *m_pGame;
	CPlPrint m_Print;

	void DrawField();
	void DrawBorder();
	void DrawBall(int id);

public:
	void GLInit();
	void DrawScene(CFDGame *game);
	void UnloadTextures();
	void LoadTextures();
	CFDDraw(void);
	~CFDDraw(void);
};

#endif // __391072E335AAC88281F9BA__DRAW__HPP__
