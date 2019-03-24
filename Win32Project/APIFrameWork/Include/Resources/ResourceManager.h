#pragma once

#include "../Game.h"
class CResourceManager
{
private:
	unordered_map<string, class CTexture*> m_mapTexture;

public:
	class CTexture* LoadTexture(const string& strKey, const wchar_t* pFileName, const string& strPathKey);
	DECLARE_SINGLE(CResourceManager)
};

