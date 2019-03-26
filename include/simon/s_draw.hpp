#ifndef __509C12FB189F8E844F5682__S_DRAW__HPP__
#define __509C12FB189F8E844F5682__S_DRAW__HPP__

#include <kos.h>

#include "dccommon/gldraw.hpp"
#include "dccommon/plprint.hpp"
#include "main/gp_draw.hpp"
#include "simon/s_game.hpp"

class CSDraw : public CGPDraw
{
private:
	GLuint m_ArrowTexture;
	GLuint m_BackgroundTexture;
	GLuint m_MainMenuTextures[5];
	GLuint m_GameTextures[6];

	bool m_ListFinished;

	CSGame *m_pGame;
	CPlPrint *m_pPrint;

	void UnloadTextures();
	void LoadTextures();
public:
	void DrawScene(CSGame *game);

	CSDraw(void);
	~CSDraw(void);
};


#endif // __509C12FB189F8E844F5682__S_DRAW__HPP__
