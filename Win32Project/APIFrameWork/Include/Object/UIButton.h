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

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CUIButton* Clone();
};

