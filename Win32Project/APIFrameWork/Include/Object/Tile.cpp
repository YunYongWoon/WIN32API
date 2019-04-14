#include "Tile.h"



CTile::CTile() : m_eOption(TO_NONE) {
}

CTile::CTile(const CTile & tile) : CStaticObj(tile) {
	m_eOption = tile.m_eOption;
}


CTile::~CTile() {
}

bool CTile::Init() {
	return true;
}

void CTile::Input(float fDeltaTime) {

	CStaticObj::Input(fDeltaTime);
}

int CTile::Update(float fDeltaTime) {

	CStaticObj::Update(fDeltaTime);
	return 0;
}

int CTile::LateUpdate(float fDeltaTime) {
	CStaticObj::LateUpdate(fDeltaTime);
	return 0;
}

void CTile::Collision(float fDeltaTime) {
	CStaticObj::Collision(fDeltaTime);
}

void CTile::Render(HDC hDC, float fDeltaTime) {
	CStaticObj::Render(hDC, fDeltaTime);
}

CTile * CTile::Clone() {
	return new CTile(*this);
}
