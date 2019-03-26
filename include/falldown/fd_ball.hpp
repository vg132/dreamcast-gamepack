#ifndef __2357F92023C4B57BED8F8__FD_BALL__HPP__
#define __2357F92023C4B57BED8F8__FD_BALL__HPP__

#include <kos.h>
#include <math.h>

class CFDBall
{
private:
	int m_iSize;
	int m_iSpeed;
	float m_fX;
	float m_fY;
	float m_fDropSpeed;
	float m_fAcceleration;
	int m_iAngle;
	float m_fR;
	float m_fG;
	float m_fB;
public:
	int GetAngle(){return(m_iAngle);};
	void SetAngle(int angle){m_iAngle=angle;};
	int GetSize(){return(m_iSize);};
	float GetX(){return(m_fX);};
	void SetX(float x){m_fX=x;};
	float GetY(){return(m_fY);};
	void SetY(float y){m_fY=y;};
	int GetSpeed(){return(m_iSpeed);};
	void SetSpeed(int speed){m_iSpeed=speed;};
	void SetPlayer(int nr);
	float GetRed(){return(m_fR);};
	float GetGreen(){return(m_fG);};
	float GetBlue(){return(m_fB);};
	bool Intersect(CFDBall *ball);

	float GetAcceleration(){return(m_fAcceleration);};
	float GetDropSpeed(){return(m_fDropSpeed);};
	void SetDropSpeed(float speed){m_fDropSpeed=speed;};

	CFDBall(void);
	~CFDBall(void);
};

#endif // __2357F92023C4B57BED8F8__FD_BALL__HPP__
