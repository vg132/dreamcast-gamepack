#ifndef __627360D4A9BE220BA1F18__MENUMAKER__HPP__
#define __627360D4A9BE220BA1F18__MENUMAKER__HPP__

#include <kos.h>

#include "dccommon/gldraw.hpp"

class CGPDraw : public CGLDraw
{
private:
	GLuint m_iArrow;
public:
	void DrawMenu(GLuint arrow, GLuint background, GLuint items[], uint8 size, uint8 pos, uint8 offset=0);
	CGPDraw(void);
	~CGPDraw(void);
};

#endif // __627360D4A9BE220BA1F18__MENUMAKER__HPP__
