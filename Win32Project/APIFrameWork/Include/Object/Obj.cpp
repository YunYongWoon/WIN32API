#include "Obj.h"
#include "../Scene/Layer.h"

list<CObj*> CObj::m_ObjList;
unordered_map<string, CObj*> CObj::m_mapPrototype;

CObj::CObj() { 
}

CObj::CObj(const CObj & obj) {
	*this = obj;
}


CObj::~CObj() {
}

void CObj::AddObj(CObj * pObj) {
	pObj->AddRef();
	m_ObjList.push_back(pObj);
}

CObj * CObj::FindObject(const string & strTag) {
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; iter++) {
		if ((*iter)->GetTag() == strTag) {
			(*iter)->AddRef();
			return *iter;
		}
	}
	return NULL;
}

void CObj::EraseObj(CObj * pObj) {
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; iter++) {
		if (*iter == pObj) {
			SAFE_RELEASE((*iter));
			iter = m_ObjList.erase(iter);
			return;
		}
	}
}

void CObj::EraseObj(const string & strTag) {
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; iter++) {
		if ((*iter)->GetTag() == strTag) {
			SAFE_RELEASE((*iter));
			iter = m_ObjList.erase(iter);
			return;
		}
	}
}

void CObj::EraseObj() {
	Safe_Release_VecList(m_ObjList);
}

void CObj::ErasePrototype(const string & strTag) {
	unordered_map<string, CObj*>::iterator iter = m_mapPrototype.find(strTag);
	if (!iter->second) {
		return;
	}
	SAFE_RELEASE(iter->second);
	m_mapPrototype.erase(iter);
}

void CObj::ErasePrototype() {
	Safe_Release_Map(m_mapPrototype);
}

bool CObj::Init() {
	return true;
}

void CObj::Input(float fDeltaTime) {

}

int CObj::Update(float fDeltaTime) {
	return 0;
}

int CObj::LateUpdate(float fDeltaTime) {
	return 0;
}

void CObj::Collision(float fDeltaTime) {

}

void CObj::Render(HDC hDC, float fDeltaTime) {

}

CObj * CObj::CreateCloneObj(const string & strPrototypeKey, 
	const string & strTag, class CLayer* pLayer) {
	CObj* pProto = FindPrototype(strPrototypeKey);

	if (!pProto)
		return NULL;

	CObj* pObj = pProto->Clone();

	pObj->SetTag(strTag);

	if (pLayer) {
		pLayer->AddObject(pObj);
	}
	AddObj(pObj);

	return pObj;
}

CObj * CObj::FindPrototype(const string & strKey) {
	unordered_map<string, CObj*>::iterator iter = m_mapPrototype.find(strKey);

	if (iter == m_mapPrototype.end())
		return NULL;

	return iter->second;
}
