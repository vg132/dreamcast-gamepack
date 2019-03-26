#ifndef __7D935EB96D6B76D715599__ST_DRAW__HPP__
#define __7D935EB96D6B76D715599__ST_DRAW__HPP__

#include <kos.h>

#include "dccommon/gldraw.hpp"
#include "dccommon/plprint.hpp"
#include "main/gp_draw.hpp"
#include "starter/st_game.hpp"

class CSTDraw : public CGPDraw
{
private:
	GLuint m_ArrowTexture;
	GLuint m_BackgroundTexture;
	GLuint m_MainMenuTextures[5];
	GLuint m_GameTextures[6];

	bool m_ListFinished;

	CPlPrint *m_pPrint;
	CSTGame *m_pGame;

	void UnloadTextures();
	void LoadTextures();
	void DrawLights();
public:
	int32 xx,yy;
	void DrawScene(CSTGame *game);

	CSTDraw(void);
	~CSTDraw(void);
};


#endif // __7D935EB96D6B76D715599__ST_DRAW__HPP__
