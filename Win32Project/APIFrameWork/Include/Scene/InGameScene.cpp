#include "InGameScene.h"
#include "../Object/Player.h"
#include "Layer.h"

CInGameScene::CInGameScene() {
}


CInGameScene::~CInGameScene() {
}

bool CInGameScene::Init() {
	// 부모 Scene클래스이 초기화 함수를 호출
	if (!CScene::Init())
		return false;
	
	return true;
}
