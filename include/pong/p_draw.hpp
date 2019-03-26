#ifndef __1AE24C58EA6DBE76396038__P_DRAW__HPP__
#define __1AE24C58EA6DBE76396038__P_DRAW__HPP__

#include <kos.h>

#include "dccommon/gldraw.hpp"
#include "dccommon/plprint.hpp"
#include "main/gp_draw.hpp"
#include "pong/p_game.hpp"
#include "pong/p_ball.hpp"

class CPDraw : public CGPDraw
{
private:
	GLuint m_ArrowTexture;
	GLuint m_BackgroundTexture;
	GLuint m_MainMenuTextures[3];
	GLuint m_GameTextures[6];

	bool m_ListFinished;

	CPGame *m_pGame;
	CPlPrint *m_pPrint;

	void UnloadTextures();
	void LoadTextures();

	void DrawBorder(float width=50.0f, float height=50.0f,float depth=10.0f);
	void DrawBall(CPBall *ball);
public:
	void DrawScene(CPGame *game);

	CPDraw(void);
	~CPDraw(void);
};


#endif // __1AE24C58EA6DBE76396038__P_DRAW__HPP__
