#include "SceneManager.h"
#include "InGameScene.h"

DEFINITION_SINGLE(CSceneManager)

CSceneManager::CSceneManager() : m_pScene(NULL) {

}


CSceneManager::~CSceneManager() {
	SAFE_DELETE(m_pScene);
}

bool CSceneManager::Init() {
	CreateScene<CInGameScene>(SC_CURRENT);
	return true;
}
