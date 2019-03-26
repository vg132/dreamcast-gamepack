#ifndef __3864807E76E5ED337CA3__ST_PLAYER__HPP__
#define __3864807E76E5ED337CA3__ST_PLAYER__HPP__

#include <kos.h>

class CSTPlayer
{
private:
	uint64 m_BestTime;
	char *m_BestTimeString;
	bool m_Playing;
public:
	uint64 GetBestTime(){return(m_BestTime);};
	char* GetBestTimeString(){return(m_BestTimeString);};
	void SetBestTime(uint64 time, char *timeString);
	bool IsPlaying(){return(m_Playing);};
	void SetPlaying(bool playing){m_Playing=playing;};

	CSTPlayer(void);
	~CSTPlayer(void);
};


#endif // __3864807E76E5ED337CA3__ST_PLAYER__HPP__
