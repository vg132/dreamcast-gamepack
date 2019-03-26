#include "minesweeper/ms_field.hpp"

CMSField::CMSField(uint16 width, uint16 height, uint16 mines)
: m_Marked(0), m_CorrectlyMarked(0), m_Won(false)
{
	m_Width=width;
	m_Height=height;
	m_Tiles=width*height;
	m_VisitedTiles=new bool[m_Tiles];
	m_MineField=new CMSTile[m_Tiles];
	m_Mines=mines;

	uint16 nr(0);
	for(uint16 i=0;i<m_Mines;i++)
	{
		do
		{
			nr=Random(m_Tiles);
		}while(m_MineField[nr].IsMine()==true);
		m_MineField[nr].SetMine(true);
	}
}

CMSField::~CMSField(void)
{
	delete[] m_MineField;
	delete[] m_VisitedTiles;
}

void CMSField::MarkTile(uint16 pos)
{
	m_MineField[pos].Mark();
	if(m_MineField[pos].IsMine())
	{
		if(m_MineField[pos].IsMarked())
			m_CorrectlyMarked++;
		else
			m_CorrectlyMarked--;
	}
	if(m_MineField[pos].IsMarked())
		m_Marked++;
	else
		m_Marked--;
	m_Won=CheckIfWon();
}

uint16 CMSField::Random(uint16 limit)
{
	return((rand())%limit);
}

void CMSField::ClearVisitedTiles()
{
	for(int i=0;i<m_Tiles;i++)
		m_VisitedTiles[i]=false;
}

bool CMSField::Open(uint16 pos)
{	
	uint16 y(0);
	while(m_Width<=pos)
	{
		pos-=m_Width;
		y++;
	}
	return(Open(pos,y));
}

bool CMSField::Open(uint16 x, uint16 y)
{
	ClearVisitedTiles();
	bool ret=RunOpen(x,y);
	m_Won=CheckIfWon();
	return(ret);
}

bool CMSField::RunOpen(uint16 x, uint16 y)
{
	if(x>=m_Width)
		return(false);
	if(y>=m_Height)
		return(false);

	int pos=(y*m_Width)+x;
	if((m_VisitedTiles[pos]==true)||(m_MineField[pos].IsOpen()==true))
		return(false);
	else
		m_VisitedTiles[pos]=true;
	m_MineField[pos].SetOpen(true);
	if(m_MineField[pos].IsMine()==true)
		return(false);
	uint8 mines=0;
	if(Check(x-1,y-1))
		mines++;
	if(Check(x, y-1))
		mines++;
	if(Check(x+1, y-1))
		mines++;
	if(Check(x+1, y))
		mines++;
	if(Check(x+1, y+1))
		mines++;
	if(Check(x, y+1))
		mines++;
	if(Check(x-1, y+1))
		mines++;
	if(Check(x-1, y))
		mines++;
	if(mines==0)
	{
		RunOpen(x-1,y-1);
		RunOpen(x, y-1);
		RunOpen(x+1,y-1);
		RunOpen(x+1, y);
		RunOpen(x+1,y+1);
		RunOpen(x, y+1);
		RunOpen(x-1,y+1);
		RunOpen(x-1, y);
	}
	else
	{
		m_MineField[pos].SetMines(mines);
	}
	return(true);
}

bool CMSField::Check(uint16 x, uint16 y)
{
	if(x>=m_Width)
		return(false);
	if(y>=m_Height)
		return(false);
	if(m_MineField[(y*m_Width)+x].IsMine()==true)
		return(true);
	else
		return(false);
}

CMSTile* CMSField::GetTile(uint16 pos)
{
	if(pos<m_Tiles)
		return(&m_MineField[pos]);
	return(NULL);
}

CMSTile* CMSField::GetTile(uint16 x, uint16 y)
{
	return(GetTile((y*m_Width)+x));
}

bool CMSField::CheckIfWon()
{
	for(int i=0;i<m_Tiles;i++)
	{
		if((m_MineField[i].IsMine()==false)&&(m_MineField[i].IsOpen()==false))
			return(false);
	}
	return(true);
}
