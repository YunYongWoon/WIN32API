#include "ResourceManager.h"
#include "Texture.h"

DEFINITION_SINGLE(CResourceManager)

CResourceManager::CResourceManager() {
}


CResourceManager::~CResourceManager() {
	Safe_Release_Map(m_mapTexture);
}

CTexture * CResourceManager::LoadTexture(const string & strKey, 
	const wchar_t * pFileName, const string & strPathKey) {
	return nullptr;
}
