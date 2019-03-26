#ifndef __A71AA1EBC49DE4479EE2__MS_DRAW__HPP__
#define __A71AA1EBC49DE4479EE2__MS_DRAW__HPP__

#include <kos.h>

#include "dccommon/gldraw.hpp"
#include "dccommon/plprint.hpp"
#include "main/gp_draw.hpp"
#include "minesweeper/ms_game.hpp"
#include "minesweeper/ms_field.hpp"

class CMSDraw : public CGPDraw
{
private:
	GLuint m_ArrowTexture;
	GLuint m_BackgroundTextures[1];
	GLuint m_MainMenuTextures[4];
	GLuint m_PauseMenuTextures[2];
	GLuint m_GameTextures[15];

	float m_Zoom;
	float m_XRot;
	float m_YRot;

	bool m_ListFinished;
	

	CPlPrint *m_pPrint;

	CMSGame *m_pGame;
	void DrawField();
	void UnloadTextures();
	void LoadTextures();
public:
	int xx;
	int yy;
	void ResetView();
	float GetZoom(){return(m_Zoom);};
	void SetZoom(float zoom){m_Zoom=zoom;};
	float GetXRot(){return(m_XRot);};
	void SetXRot(float x){m_XRot=x;};
	float GetYRot(){return(m_YRot);};
	void SetYRot(float y){m_YRot=y;};


	void DrawScene(CMSGame *game);
	CMSDraw(void);
	~CMSDraw(void);
};

#endif // __A71AA1EBC49DE4479EE2__MS_DRAW__HPP__
