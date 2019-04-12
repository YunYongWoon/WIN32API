#include "Input.h"
#include "../Object/Mouse.h"
#include "../Animation/Animation.h"
#include "../Scene/Layer.h"
#include "../Collider/CollisionManager.h"

DEFINITION_SINGLE(CInput)

CInput::CInput() : m_pCreateKey(NULL), m_pMouse(NULL) {
}


CInput::~CInput() {
	SAFE_RELEASE(m_pMouse);
	Safe_Delete_Map(m_mapKey);
}

bool CInput::Init(HWND hWnd) {
	m_hWnd = hWnd;

	AddKey('W', "MoveUp");
	AddKey('S', "MoveBottom");
	AddKey("MoveLeft", 'A');
	AddKey("MoveRight", 'D');
	AddKey("Fire", VK_SPACE);
	AddKey(VK_CONTROL, "Skill1", '1');
	AddKey(VK_LBUTTON, "MouseLButton");

	// 마우스 위치를 얻어오는 함수
	GetCursorPos(&m_tMousePos);

	// 마우스 생성
	m_pMouse = CObj::CreateObj<CMouse>("Mouse");

	m_pMouse->SetSize(32, 31);

	CAnimation* pAni = m_pMouse->CreateAnimation("PlayerAnimation");

	vector<wstring> vecFileName;

	for (int i = 0; i <= 3; i++) {
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Mouse/%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	m_pMouse->AddAnimationClip("MouseNormal", AT_FRAME, AO_LOOP, 1.f, 4, 1,
		0, 0, 4, 1, 0.f, "MouseNormal", vecFileName);
	m_pMouse->SetAnimationClipColorKey("MouseNormal", 0, 255, 0);

	SAFE_RELEASE(pAni);

	return true;
}

void CInput::Update(float fDeltaTime) {
	unordered_map<string, PKEYINFO>::iterator iter;
	unordered_map<string, PKEYINFO>::iterator iterEnd = m_mapKey.end();

	for (iter = m_mapKey.begin(); iter != iterEnd; ++iter) {
		int iPushCount = 0;
		for (size_t i = 0; i < iter->second->vecKey.size(); ++i) {
			if (GetAsyncKeyState(iter->second->vecKey[i]) & 0x8000)
				++iPushCount;
		}

		if (iPushCount == iter->second->vecKey.size()) {
			if (!iter->second->bDown && !iter->second->bPress) {
				iter->second->bPress = true;
				iter->second->bDown = true;
			}
			else if (iter->second->bDown)
				iter->second->bDown = false;
		}

		else {
			if (iter->second->bDown || iter->second->bPress) {
				iter->second->bUp = true;
				iter->second->bDown = false;
				iter->second->bPress = false;
			}
			else if (iter->second->bUp)
				iter->second->bUp = false;
		}
	}

	m_pMouse->Update(fDeltaTime);
	m_pMouse->LateUpdate(fDeltaTime);

}

bool CInput::KeyDown(const string & strKey) const {
	PKEYINFO pInfo = FindKey(strKey);

	if (!pInfo)
		return false;
	return pInfo->bDown;
}

bool CInput::KeyPress(const string & strKey) const {
	PKEYINFO pInfo = FindKey(strKey);

	if (!pInfo)
		return false;

	return pInfo->bPress;
}

bool CInput::KeyUp(const string & strKey) const {
	PKEYINFO pInfo = FindKey(strKey);

	if (!pInfo)
		return false;

	return pInfo->bUp;
}

PKEYINFO CInput::FindKey(const string & strKey) const {

	unordered_map<string, PKEYINFO>::const_iterator iter = m_mapKey.find(strKey);

	if (iter == m_mapKey.end())
		return NULL;

	return iter->second;
}
