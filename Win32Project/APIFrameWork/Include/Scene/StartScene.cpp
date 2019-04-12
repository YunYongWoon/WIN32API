#include "StartScene.h"
#include "../Object/UIPanel.h"
#include "../Object/UIButton.h"
#include "Layer.h"
#include "../Core/Camera.h"
#include "../Collider/ColliderPixel.h"
#include "../Collider/ColliderRect.h"
#include "../Core.h"

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

	CUIButton* pStartButton = CObj::CreateObj<CUIButton>("StartButton", pLayer);

	pStartButton->SetPos(GETRESOLUTION.iW / 2 - 250, GETRESOLUTION.iH / 2 + 150);
	pStartButton->SetSize(200, 100);
	pStartButton->SetTexture("StartButton", L"StartButton.bmp");

	CColliderRect* pRC = (CColliderRect*)pStartButton->GetCollider("ButtonBody");

	POSITION tPos = pStartButton->GetPos();
	pRC->SetRect(tPos.x, tPos.y, tPos.x + 200, tPos.y + 100);

	SAFE_RELEASE(pRC);
	SAFE_RELEASE(pStartButton);

	CUIButton* pEndButton = CObj::CreateObj<CUIButton>("EndButton", pLayer);

	pEndButton->SetPos(GETRESOLUTION.iW / 2 + 20 , GETRESOLUTION.iH / 2 + 150);
	pEndButton->SetSize(200, 100);
	pEndButton->SetTexture("EndButton", L"EndButton.bmp");

	pRC = (CColliderRect*)pEndButton->GetCollider("ButtonBody");

	tPos = pEndButton->GetPos();
	pRC->SetRect(tPos.x, tPos.y, tPos.x + 200, tPos.y + 100);

	SAFE_RELEASE(pRC);
	SAFE_RELEASE(pEndButton);
	return true;
}
