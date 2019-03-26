#include "pong/p_ball.hpp"

CPBall::CPBall(float x, float y, float radius, float velocityX, float velocityY)
: m_Hit(false), m_VelocityX(velocityX), m_VelocityY(velocityY)
{
	m_pRect=new CRect(x,y,radius*2,radius*2);
}

CPBall::~CPBall(void)
{
	if(m_pRect!=NULL)
		delete m_pRect;
}

void CPBall::Move()
{
	m_pRect->SetX(m_pRect->GetX()+m_VelocityX);
	m_pRect->SetY(m_pRect->GetY()+m_VelocityY);

	if(m_VelocityX>5)
		m_VelocityX=5;
	if(m_VelocityX<-5)
		m_VelocityX=-5;
	if(m_VelocityY>5)
		m_VelocityY=5;
	if(m_VelocityY<-5)
		m_VelocityY=-5;
}

void CPBall::Bounce(bool x)
{
	if(x==true)
		m_VelocityX=-1.1f*m_VelocityX;
	else
		m_VelocityY=-1.1f*m_VelocityY;
}
