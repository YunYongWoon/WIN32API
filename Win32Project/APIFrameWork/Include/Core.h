#pragma once
#include "Game.h"

class CCore
{
private:
	static CCore* m_pInst;

public:
	static CCore* GetInst() {
		if (!m_pInst) 
			m_pInst = new CCore;
		return m_pInst;
	}

	static void DestroyInst() {
		SAFE_DELETE(m_pInst);
	}

private:
	CCore();
	~CCore();
};

