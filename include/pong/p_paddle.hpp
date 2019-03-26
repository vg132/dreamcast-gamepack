#ifndef __C08089F03D6490FD5A159__P_PADDLE__HPP__
#define __C08089F03D6490FD5A159__P_PADDLE__HPP__

#include <kos.h>

class CPPaddle
{
private:
	uint16 m_X;
	uint16 m_Y;
public:
	uint16 GetX(){return(m_X);};
	void SetX(uint16 x){m_X=x;};
	uint16 GetY(){return(m_Y);};
	void SetY(uint16 y){m_Y=y;};
	void MoveUp(){m_Y--;};
	void MoveDown(){m_Y++;};
	CPPaddle(uint16 x, uint16 y);
	~CPPaddle(void);
};


#endif // __C08089F03D6490FD5A159__P_PADDLE__HPP__
