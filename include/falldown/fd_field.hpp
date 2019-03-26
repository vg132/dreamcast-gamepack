#ifndef __4315446B5928BF1566F59__FD_FIELD__HPP__
#define __4315446B5928BF1566F59__FD_FIELD__HPP__

#include <kos.h>
#include <stdlib.h>

struct BlockSet_t
{
	int i_Blocks[16];
	int i_Height;
};

class CFDField
{
private:
	int m_iBlockWidth;
	int m_iBlockSpeed;
	BlockSet_t m_Blocks[6];
public:
	BlockSet_t* GetRow(int row){return(&m_Blocks[row]);};
	int GetBlockWidth(){return(m_iBlockWidth);};
	int GetBlockSpeed(){return(m_iBlockSpeed);};

	void MakeBlock(int row);
	CFDField(void);
	~CFDField(void);
};

#endif // __4315446B5928BF1566F59__FD_FIELD__HPP__
