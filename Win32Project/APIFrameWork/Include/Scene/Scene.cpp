#include "Scene.h"
#include "Layer.h"

CScene::CScene() {
	CLayer* pLayer = CreateLayer("Default",INT_MIN);
	pLayer = CreateLayer("UI", INT_MAX);
}

CScene::~CScene() {
	Safe_Delete_VecList(m_LayerList);
}

CLayer * CScene::CreateLayer(const string & strTag, int iZOrder) {
	CLayer* pLayer = new CLayer;

	pLayer->SetTag(strTag);
	pLayer->SetZOrder(iZOrder);
	pLayer->SetScene(this);

	m_LayerList.push_back(pLayer);

	if (m_LayerList.size() >= 2)
		m_LayerList.sort(CScene::LayerSort);

	return pLayer;
}

bool CScene::Init() {
	return false;
}

bool CScene::LayerSort(CLayer *pL1, CLayer *pL2) {
	return pL1->GetZOrder() < pL2->GetZOrder();
}
