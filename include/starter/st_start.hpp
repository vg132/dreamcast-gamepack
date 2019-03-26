#ifndef __68F46EF3D9116E67744250__ST_START__HPP__
#define __68F46EF3D9116E67744250__ST_START__HPP__

#include <kos.h>
#include <time.h>

class CSTStart
{
private:
	char *m_pText;
	uint8 m_State;
public:
	static const uint8 STATE_TEXT=0;
	static const uint8 STATE_RUN=1;

	virtual void Start(){};
	char* GetText(){return(m_pText);};
	uint8 GetState(){return(m_State);};
	void SetState(uint8 state){m_State=state;};
	CSTStart(void);
	virtual ~CSTStart(void);
};


#endif // __68F46EF3D9116E67744250__ST_START__HPP__
