#include "MapEditScene.h"
#include "../Object/Stage.h"
#include "Layer.h"
#include "../Core/Camera.h"
#include "../Collider/ColliderPixel.h"
#include "../Collider/ColliderRect.h"
#include "../Core.h"
#include "SceneManager.h"
#include "StartScene.h"

CMapEditScene::CMapEditScene() {
}


CMapEditScene::~CMapEditScene() {
}

bool CMapEditScene::Init() {
	GET_SINGLE(CCamera)->SetWorldResolution(1920, 1080);
	CLayer* pStageLayer = FindLayer("Stage");

	CStage* pStage = CObj::CreateObj<CStage>("Stage", pStageLayer);

	pStage->CreateTile(40, 40, 48, 27, "BaseTile", L"Tile/Tile2.bmp");

	SAFE_RELEASE(pStage);
	return true;
}

void CMapEditScene::Input(float fDeltaTime) {
	CScene::Input(fDeltaTime);

	if (GetAsyncKeyState('W') & 0x8000) {
		GET_SINGLE(CCamera)->Scroll(0.f, -300.f * fDeltaTime);
	}
	if (GetAsyncKeyState('S') & 0x8000) {
		GET_SINGLE(CCamera)->Scroll(0.f, 300.f * fDeltaTime);
	}
	if (GetAsyncKeyState('A') & 0x8000) {
		GET_SINGLE(CCamera)->Scroll(-300.f * fDeltaTime, 0.f);
	}
	if (GetAsyncKeyState('D') & 0x8000) {
		GET_SINGLE(CCamera)->Scroll(300.f * fDeltaTime, 0.f);
	}
}
