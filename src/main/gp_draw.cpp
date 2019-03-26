#include "main/gp_draw.hpp"

CGPDraw::CGPDraw(void)
{
}

CGPDraw::~CGPDraw(void)
{
}

void CGPDraw::DrawMenu(GLuint arrow, GLuint background, GLuint items[], uint8 size, uint8 pos, uint8 offset)
{
	DrawBackground(background);
	glKosFinishList();

	PushMatrices();
	SetOrtho();

	for(int i=0;i<size;i++)
		TexturedRect(items[i],189.0f,160.0f-(i*50),256.0f,256.0f);
	TexturedRect(arrow,200.0f-offset,275.0f-(pos*50),32.0f,32.0f);

	PopMatrices();
}
