#ifndef __AAFD4291534026F44AE8CC__P_BALL__HPP__
#define __AAFD4291534026F44AE8CC__P_BALL__HPP__

#include <kos.h>
#include <stdlib.h>
#include "dccommon/rect.hpp"

class CPBall
{
private:
	bool m_Hit;
	CRect *m_pRect;
	float m_VelocityX;
	float m_VelocityY;
public:
	bool GetHit(){return(m_Hit);};
	void SetHit(bool hit){m_Hit=hit;};
	CRect* GetRect(){return(m_pRect);};
	void SetRect(CRect *rect){m_pRect=rect;};
	float GetVelocityX(){return(m_VelocityX);};
	void SetVelocityX(float velocity){m_VelocityX=velocity;};
	float GetVelocityY(){return(m_VelocityY);};
	void SetVelocityY(float velocity){m_VelocityY=velocity;};

	void Move();
	void Bounce(bool x);

	CPBall(float x, float y,float radius, float velocityX, float velocityY);
	~CPBall(void);
};


#endif // __AAFD4291534026F44AE8CC__P_BALL__HPP__
