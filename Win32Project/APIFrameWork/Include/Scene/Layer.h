#pragma once

#include "..\Game.h"
class CLayer
{
private:
	friend class CScene;

private:
	CLayer();

public: 
	~CLayer();

private:
	class CScene* m_pScene;
	string m_strTag;
	int	m_iZOrder;			// 레이어 중 어떤 것부터 출력할지 결정(나중에 출력할 것이 먼저 출력할 것을 덮어버린다.
	list<class CObj*> m_ObjList;

public:
	void SetTag(const string& strTag) {
		m_strTag = strTag;
	}

	void SetZOrder(int iZOrder) {
		m_iZOrder = iZOrder;
	}

	void SetScene(class CScene* pScene) {
		m_pScene = pScene;
	}

	int GetZOrder() const {
		return m_iZOrder;
	}

	string GetTag() const {
		return m_strTag;
	}

	CScene* GetScene() const {
		return m_pScene;
	}
	
public:
	void AddObject(class CObj* pObj);

public:
	 void Input(float fDeltaTime);
	 int Update(float fDeltaTime);
	 int LateUpdate(float fDeltaTime);
	 void Collision(float fDeltaTime);
	 void Render(HDC hDC, float fDeltaTime);
};

