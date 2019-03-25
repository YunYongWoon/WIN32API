#include "InGameScene.h"
#include "../Object/Player.h"
#include "../Object/Minion.h"
#include "../Object/Bullet.h"
#include "../Object/Stage.h"
#include "Layer.h"

CInGameScene::CInGameScene() {
}


CInGameScene::~CInGameScene() {
}

bool CInGameScene::Init() {
	// �θ� SceneŬ������ �ʱ�ȭ �Լ��� ȣ��
	if (!CScene::Init())
		return false;

	CLayer* pLayer = FindLayer("Default");

	CLayer* pStageLayer = FindLayer("Stage");
	CStage* pStage = CObj::CreateObj<CStage>("Stage", pLayer);
	SAFE_RELEASE(pStage);

	CPlayer* pPlayer = CObj::CreateObj<CPlayer>("Player", pLayer);
	SAFE_RELEASE(pPlayer);

	CMinion* pMinion = CObj::CreateObj<CMinion>("Minion", pLayer);
	SAFE_RELEASE(pMinion);

	// �Ѿ� ������Ÿ��
	CBullet* pBullet = CScene::CreatePrototype<CBullet>("Bullet");
	pBullet->SetSize(50.f, 50.f);
	SAFE_RELEASE(pBullet);


	return true;
}
