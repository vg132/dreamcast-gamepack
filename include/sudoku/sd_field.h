#ifndef __F21B5AEBFEA2688FDB75__SD_FIELD__H__
#define __F21B5AEBFEA2688FDB75__SD_FIELD__H__

#include <kos.h>
#include <stdlib.h>

#include "sudoku/sd_tile.hpp"
#include "sudoku/sudokufields.hpp"

class CSDField
{
private:
	CSDTile *m_SudokuField;
	uint16 *m_CurrentField;
	uint16 m_Width;
	uint16 m_Height;

	bool Check(uint16 x, uint16 y);
	bool CheckIfWon();
public:
	void NewField();
	CSDField(void);
	~CSDField(void);
};


#endif // __F21B5AEBFEA2688FDB75__SD_FIELD__H__
