#include "StartScene.h"
#include "../Object/UIPanel.h"
#include "../Object/UIButton.h"
#include "Layer.h"
#include "../Core/Camera.h"
#include "../Collider/ColliderPixel.h"
#include "../Collider/ColliderRect.h"
#include "../Core.h"
#include "SceneManager.h"
#include "InGameScene.h"
#include "MapEditScene.h"

CStartScene::CStartScene() {

}


CStartScene::~CStartScene() {
}

bool CStartScene::Init() {
	// 부모 Scene클래스이 초기화 함수를 호출
	if (!CScene::Init())
		return false;

	CLayer* pLayer = FindLayer("UI");

	CUIPanel* pBackPanel = CObj::CreateObj<CUIPanel>("BackPanel", pLayer);

	pBackPanel->SetSize(GETRESOLUTION.iW, GETRESOLUTION.iH);
	pBackPanel->SetTexture("StartBack", L"StartBack.bmp");

	SAFE_RELEASE(pBackPanel);

	// 시작버튼 구현
	CUIButton* pStartButton = CObj::CreateObj<CUIButton>("StartButton", pLayer);

	pStartButton->SetPos(GETRESOLUTION.iW / 2 - 250, GETRESOLUTION.iH / 2 + 150);
	pStartButton->SetSize(200, 100);
	pStartButton->SetTexture("StartButton", L"StartButton.bmp");

	CColliderRect* pRC = (CColliderRect*)pStartButton->GetCollider("ButtonBody");

	POSITION tPos = pStartButton->GetPos();
	pRC->SetRect(0.f, 0.f, 200, 100);

	SAFE_RELEASE(pRC);

	pStartButton->SetCallback(this, &CStartScene::StartButtonCallback);

	SAFE_RELEASE(pStartButton);

	// 에디터버튼 구현
	CUIButton* pEditerButton = CObj::CreateObj<CUIButton>("EditerButton", pLayer);

	pEditerButton->SetPos(GETRESOLUTION.iW / 2 - 100, GETRESOLUTION.iH / 2);
	pEditerButton->SetSize(200, 100);
	pEditerButton->SetTexture("EditerButton", L"EditerButton.bmp");

	pRC = (CColliderRect*)pEditerButton->GetCollider("ButtonBody");
	
	pRC->SetRect(0.f, 0.f, 200, 100);

	SAFE_RELEASE(pRC);

	pEditerButton->SetCallback(this, &CStartScene::EditerButtonCallback);

	SAFE_RELEASE(pEditerButton);

	// 종료버튼 구현
	CUIButton* pEndButton = CObj::CreateObj<CUIButton>("EndButton", pLayer);

	pEndButton->SetPos(GETRESOLUTION.iW / 2 + 20 , GETRESOLUTION.iH / 2 + 150);
	pEndButton->SetSize(200, 100);
	pEndButton->SetTexture("EndButton", L"EndButton.bmp");

	pRC = (CColliderRect*)pEndButton->GetCollider("ButtonBody");

	pRC->SetRect(0.f, 0.f, 200, 100);

	SAFE_RELEASE(pRC);

	pEndButton->SetCallback(this, &CStartScene::EndButtonCallback);

	SAFE_RELEASE(pEndButton);
	return true;
}

void CStartScene::StartButtonCallback(float fTime) {
	GET_SINGLE(CSceneManager)->CreateScene<CInGameScene>(SC_NEXT);
}

void CStartScene::EditerButtonCallback(float fTime) {
	GET_SINGLE(CSceneManager)->CreateScene<CMapEditScene>(SC_NEXT);
}

void CStartScene::EndButtonCallback(float fTime) {
	GET_SINGLE(CCore)->DestroyGame();
}
