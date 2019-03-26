#ifndef __D0C7A8A151150A406A9B__MS_FIELD__HPP__
#define __D0C7A8A151150A406A9B__MS_FIELD__HPP__

#include <kos.h>
#include <stdlib.h>

#include "minesweeper/ms_tile.hpp"

class CMSField
{
private:
	CMSTile *m_MineField;
	uint16 m_Width;
	uint16 m_Height;
	uint16 m_Mines;
	uint16 m_Tiles;
	uint16 m_Marked;
	uint16 m_CorrectlyMarked;
	bool *m_VisitedTiles;
	bool m_Won;

	void ClearVisitedTiles();
	uint16 Random(uint16 limit);
	bool Check(uint16 x, uint16 y);
	bool RunOpen(uint16 x, uint16 y);
	bool CheckIfWon();
public:
	uint16 GetMarkedMines(){return(m_Marked);};
	bool HasWon(){return(m_Won);};
	void MarkTile(uint16 pos);
	bool Open(uint16 pos);
	bool Open(uint16 x, uint16 y);
	CMSTile* GetTile(uint16 x, uint16 y);
	CMSTile* GetTile(uint16 pos);
	uint16 GetWidth(){return(m_Width);};
	uint16 GetHeight(){return(m_Height);};
	uint16 GetTiles(){return(m_Tiles);};
	uint16 GetMines(){return(m_Mines);};
	CMSField(uint16 width, uint16 height, uint16 mines);
	~CMSField(void);
};


#endif // __D0C7A8A151150A406A9B__MS_FIELD__HPP__
