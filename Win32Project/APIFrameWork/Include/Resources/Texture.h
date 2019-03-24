#pragma once
#include "../Ref.h"
class CTexture :
	public CRef
{
private:
	friend class CResourceManager;

private:
	CTexture();
	~CTexture();
};

