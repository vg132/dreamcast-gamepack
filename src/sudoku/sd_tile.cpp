#include "sudoku/sd_tile.hpp"

CSDTile::CSDTile(uint8 correctNumber,uint8 numberToShow)
: m_CorrectNumber(number), m_CurrentNumber(numberToShow)
{
}

CSDTile::~CSDTile(void)
{
}
