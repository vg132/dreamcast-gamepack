#ifndef __AF3CC140E31BAA56ABF418__DRAW__HPP__
#define __AF3CC140E31BAA56ABF418__DRAW__HPP__

#include <kos.h>
#include <math.h>

#include "dccommon/gldraw.hpp"
#include "main/game.hpp"

class CDraw : public CGLDraw
{
private:
	GLuint m_iLeftArrow;
	GLuint m_iRightArrow;
	GLuint m_iBackground;
	CGame *m_pGame;

	void DrawMainMenu();
public:
#ifdef __DEBUG__
	float xx, yy;
#endif

	void GLInit();
	void DrawScene(CGame *game);

	void LoadMainTextures();
	void UnloadMainTextures();

	CDraw(void);
	~CDraw(void);
};

#endif // __AF3CC140E31BAA56ABF418__DRAW__HPP__
