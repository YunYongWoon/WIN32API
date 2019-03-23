#include "InGameScene.h"
#include "../Object/Player.h"
#include "../Object/Minion.h"
#include "Layer.h"

CInGameScene::CInGameScene() {
}


CInGameScene::~CInGameScene() {
}

bool CInGameScene::Init() {
	// 부모 Scene클래스이 초기화 함수를 호출
	if (!CScene::Init())
		return false;

	CLayer* pLayer = FindLayer("Default");

	CPlayer* pPlayer = CObj::CreateObj<CPlayer>("Player", pLayer);
	SAFE_RELEASE(pPlayer);

<<<<<<< HEAD
	CMinion* pMinion = CObj::CreateObj<CMinion>("Minion", pLayer);
	SAFE_RELEASE(pMinion);
	
=======
>>>>>>> d63d3f72a23ca8c2a58faf79d4ede9e5a09c6f64

	return true;
}
