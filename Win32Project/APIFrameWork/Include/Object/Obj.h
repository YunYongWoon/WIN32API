#pragma once

#include "../Ref.h"
class CObj : public CRef
{
protected:
	CObj();
	CObj(const CObj& obj);
	virtual ~CObj();

protected: 
	class CScene* m_pScene;
	class CLayer* m_pLayer;

public:
	void SetScene(class CScene* pScene) {
		m_pScene = pScene;
	}
	void SetLayer(class CLayer* pLayer) {
		m_pLayer = pLayer;
	}

	class CScene* GetScene() const {
		return m_pScene;
	}

	class CLayer* GetLayer() const {
		return m_pLayer;
	}

protected:
	int m_iRef;

protected:
	list<class CObj*> m_ObjList;

protected:
	string m_strTag;
	POSITION m_tPos;
	_SIZE m_tSize;
	POSITION m_tPovot;

public:
	string GetTag() const {
		return m_strTag;
	}

	POSITION GetPos() const {
		return m_tPos;
	}

	_SIZE GetSize() const {
		return m_tSize;
	}

public:
	void SetTag(const string& strTag) {
		m_strTag = strTag;
	}

	void SetPos(const POSITION& tPos) {
		m_tPos = tPos;
	}

	void SetPos(float x, float y) {
		m_tPos.x = x;
		m_tPos.y = y;
	}
	 
	void SetSize(const _SIZE& tSize) {
		m_tSize = tSize;
	}

	void SetSize(float x, float y) {
		m_tSize.x = x;
		m_tSize.y = y;
	}

public:
	virtual bool Init() = 0;
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);

public:
	template <typename T>
	static T* CreateObj(const string& strTag, class CLayer* pLayer = NULL) {
		T* pObj = new T;
		if (!pObj->Init()) {
			SAFE_RELEASE(pObj);
			return NULL;
		}

		if (pLayer) {
			pLayer->AddObject(pObj);
		}

		return pObj;
	}
};

