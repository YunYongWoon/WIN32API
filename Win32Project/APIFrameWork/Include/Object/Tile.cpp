#include "Tile.h"



CTile::CTile() {
}

CTile::CTile(const CTile & tile) : CStaticObj(tile) {
}


CTile::~CTile() {
}

bool CTile::Init() {
	return true;
}

void CTile::Input(float fDeltaTime) {
}

int CTile::Update(float fDeltaTime) {
	return 0;
}

int CTile::LateUpdate(float fDeltaTime) {
	return 0;
}

void CTile::Collision(float fDeltaTime) {
}

void CTile::Render(HDC hDC, float fDeltaTime) {
}

CTile * CTile::Clone() {
	return new CTile(*this);
}
