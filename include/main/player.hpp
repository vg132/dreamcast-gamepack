#ifndef __532D2E195C84A489EE678E__PLAYER__HPP__
#define __532D2E195C84A489EE678E__PLAYER__HPP__

#include "dccommon/dccontrol.hpp"

class CPlayer
{
private:
	char *m_pName;
	int m_iLives;
	int m_iPoints;
	CDCControl *m_pControl;
public:
	void SetControl(CDCControl *control){m_pControl=control;};
	CDCControl* GetControl(){return(m_pControl);};
	void SetLives(int lives){m_iLives=lives;};
	int GetLives(){return(m_iLives);};
	bool IsAlive(){return(m_iLives>0);};
	void SetName(const char *name);
	char* GetName(){return(m_pName);};

	CPlayer(void);
	~CPlayer(void);
};

#endif // __532D2E195C84A489EE678E__PLAYER__HPP__
