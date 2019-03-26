#include "..\..\include\ball.hpp"

CBall::CBall(void)
{
	m_fX=0.0f;
	m_fY=0.0f;
	m_iSpeed=550;
	m_iSize=20;
	m_fDropSpeed=0.0f;
	m_fAcceleration=0.04f;
	m_iAngle=0;
}

CBall::~CBall(void)
{
}

void CBall::SetPlayer(int nr)
{
	if(nr==0)
	{
		m_fR=0.0f;
		m_fG=0.0f;
		m_fB=1.0f;
	}
	else if(nr==1)
	{
		m_fR=1.0f;
		m_fG=0.0f;
		m_fB=0.0f;
	}
	else if(nr==2)
	{
		m_fR=1.0f;
		m_fG=0.0f;
		m_fB=1.0f;
	}
	else if(nr==3)
	{
		m_fR=1.0f;
		m_fG=1.0f;
		m_fB=1.0f;
	}
}

bool CBall::Intersect(CBall *ball)
{
	float x=fabs(this->GetX()-ball->GetX());
	float y=fabs(this->GetY()-ball->GetY());

	if(sqrt((x*x)+(y*y))<=6.0f)
		return(true);
	else
		return(false);
}
