#include "Obj.h"


CObj::CObj() {
}

CObj::CObj(const CObj & obj) {
	*this = obj;
}


CObj::~CObj() {
}

bool CObj::Init() {
	return true;
}

void CObj::Input(float fDeltaTime) {

	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_ObjList.end();
		 
	for (iter = m_ObjList.begin(); iter != iterEnd; iter++) {
		(*iter)->Input(fDeltaTime);
	}
}

int CObj::Update(float fDeltaTime) {

	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; iter++) {
		(*iter)->Update(fDeltaTime);
	}
	return 0;
}

int CObj::LateUpdate(float fDeltaTime) {
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; iter++) {
		(*iter)->LateUpdate(fDeltaTime);
	}
	return 0;
}

void CObj::Collision(float fDeltaTime) {
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; iter++) {
		(*iter)->Collision(fDeltaTime);
	}
}

void CObj::Render(HDC hDC, float fDeltaTime) {
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; iter++) {
		(*iter)->Render(hDC, fDeltaTime);
	}
}
