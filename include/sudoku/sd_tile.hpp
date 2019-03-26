#ifndef __50B0C8F67CB97F7F4D2979__SD_TILE__HPP__
#define __50B0C8F67CB97F7F4D2979__SD_TILE__HPP__

#include <kos.h>

class CSDTile
{
private:
	uint8 m_CurrentNumber;
	uint8 m_CorrectNumber;
public:
	uint8 GetCorrectNumber(){return(m_CorrectNumber);};
	void SetCorrectNumber(uint8 number){m_CorrectNumber=number;};
	uint8 GetCurrentNumber(){return(m_CurrentNumber);};
	void SetCurrentNumber(uint8 number){m_CurrentNumber=number;};

	CSDTile(void);
	~CSDTile(void);
};


#endif // __50B0C8F67CB97F7F4D2979__SD_TILE__HPP__
