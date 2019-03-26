#ifndef __8DF8799C58F97C1837AAA7__ST_F1__HPP__
#define __8DF8799C58F97C1837AAA7__ST_F1__HPP__

#include <kos.h>
#include "starter/st_start.hpp"

class CSTF1 : public CSTStart
{
private:
	uint64 m_StartTime;
public:
	void Start();
	CSTF1(void);
	~CSTF1(void);
};

#endif // __8DF8799C58F97C1837AAA7__ST_F1__HPP__
