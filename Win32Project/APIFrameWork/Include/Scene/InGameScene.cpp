#include "InGameScene.h"
#include "../Object/Player.h"
#include "../Object/Minion.h"
#include "../Object/Bullet.h"
#include "../Object/Stage.h"
#include "Layer.h"
#include "../Core/Camera.h"
#include "../Collider/ColliderPixel.h"

CInGameScene::CInGameScene() {
}


CInGameScene::~CInGameScene() {
}

bool CInGameScene::Init() {
	// 부모 Scene클래스이 초기화 함수를 호출
	if (!CScene::Init())
		return false;

	CLayer* pLayer = FindLayer("Default");

	CLayer* pStageLayer = FindLayer("Stage");

	CStage* pStage = CObj::CreateObj<CStage>("Stage", pStageLayer);
	CColliderPixel* pPixel = pStage->AddCollider<CColliderPixel>("StageColl");
	pPixel->SetPixelInfo("Stage1.bmp");


	SAFE_RELEASE(pPixel);
	SAFE_RELEASE(pStage);

	CPlayer* pPlayer = CObj::CreateObj<CPlayer>("Player", pLayer);
	GET_SINGLE(CCamera)->SetTarget(pPlayer);
	GET_SINGLE(CCamera)->SetPivot(0.5f,0.5f);
	SAFE_RELEASE(pPlayer);

	CMinion* pMinion = CObj::CreateObj<CMinion>("Minion", pLayer);
	SAFE_RELEASE(pMinion);

	// 총알 프로토타입
	CBullet* pBullet = CScene::CreatePrototype<CBullet>("Bullet", m_eSceneType);
	pBullet->SetSize(50.f, 50.f);
	SAFE_RELEASE(pBullet);


	return true;
}
