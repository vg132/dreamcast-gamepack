#include "falldown/fd_field.hpp"

CFDField::CFDField(void)
{
	m_Blocks[0].i_Height=-45000;
	m_Blocks[1].i_Height=-30000;
	m_Blocks[2].i_Height=-15000;
	m_Blocks[3].i_Height=0;
	m_Blocks[4].i_Height=15000;
	m_Blocks[5].i_Height=30000;
	m_iBlockWidth=6;
	//m_iBlockSpeed=300;
	m_iBlockSpeed=100;
	for(int y=0;y<6;y++)
	{
		for(int x=0;x<16;x++)
		{
			m_Blocks[y].i_Blocks[x]=0;
		}
	}
}

CFDField::~CFDField(void)
{
}

void CFDField::MakeBlock(int row)
{
	int temp=0;
	for(int i=0;i<=15;i++)
	{
		m_Blocks[row].i_Blocks[i]=randnum(7000)%4/3;
		m_Blocks[row].i_Blocks[i]=!m_Blocks[row].i_Blocks[i];
		temp=temp+m_Blocks[row].i_Blocks[i];
	}
	if(temp>=15)
		m_Blocks[row].i_Blocks[8]=0;
}
