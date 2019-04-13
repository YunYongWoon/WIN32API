#pragma once
#include "UI.h"
class CUIButton :
	public CUI
{
private:
	friend class CObj;
	friend class CScene;

private:
	CUIButton();
	CUIButton(const CUIButton& ui);
	~CUIButton();

private:
	function<void(float fTime)> m_ButtonCallback;
	bool m_bEnableCallback;

public:
	template <typename T>
	void SetCallback(T* pObj, void(T::*pFunc)(float)) {
		m_ButtonCallback = bind(pFunc, pObj, placeholders::_1);
		m_bEnableCallback = true;
	}

	void SetCallback(void(*pFunc)(float)) {
		m_ButtonCallback = bind(pFunc, placeholders::_1);
		m_bEnableCallback = true;
	}

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CUIButton* Clone();

public:
	void MouseOn(class CCollider* pSrc,
		class CCollider* pDest, float fDeltaTime);

	void MouseOut(class CCollider* pSrc,
		class CCollider* pDest, float fDeltaTime);
};

