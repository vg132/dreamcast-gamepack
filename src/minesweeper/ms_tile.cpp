#include "minesweeper/ms_tile.hpp"

CMSTile::CMSTile(void)
: m_Mine(false), m_Open(false), m_Marked(false), m_Mines(0)
{
}

CMSTile::CMSTile(bool mine, bool open)
: m_Marked(false), m_Mines(0)
{
	m_Mine=mine;
	m_Open=open;
}

CMSTile::~CMSTile(void)
{
}

void CMSTile::Mark()
{
	m_Marked=!m_Marked;
}
