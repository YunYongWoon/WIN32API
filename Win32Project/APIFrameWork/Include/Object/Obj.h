#pragma once

#include "../Game.h"
class CObj
{
protected:
	CObj();
	virtual ~CObj();

protected:
	POSITION m_tPos;
	_SIZE m_tSize;
};

