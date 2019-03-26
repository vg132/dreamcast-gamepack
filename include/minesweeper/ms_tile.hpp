#ifndef __FDED6A9C420C78F28FEB__MS_TILE__HPP__
#define __FDED6A9C420C78F28FEB__MS_TILE__HPP__

#include <kos.h>

class CMSTile
{
private:
	bool m_Mine;
	bool m_Open;
	bool m_Marked;
	uint16 m_Mines;
public:
	CMSTile(void);
	CMSTile(bool mine, bool open);
	~CMSTile(void);

	uint16 GetMines(){return(m_Mines);};
	void SetMines(uint16 mines){m_Mines=mines;};
	bool IsMine(){return(m_Mine);};
	void SetMine(bool mine){m_Mine=mine;};
	bool IsOpen(){return(m_Open);};
	void SetOpen(bool open){m_Open=open;};
	bool IsMarked(){return(m_Marked);};
	void Mark();
};


#endif // __FDED6A9C420C78F28FEB__MS_TILE__HPP__
