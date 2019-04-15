#include "Tile.h"
#include "../Resources/ResourceManager.h"
#include "../Resources/Texture.h"
#include "../Core/Camera.h"

CTile::CTile() : m_eOption(TO_NONE) {
	m_pOptionTex = GET_SINGLE(CResourceManager)->FindTexture("TileNone");
}

CTile::CTile(const CTile & tile) : CStaticObj(tile) {
	m_eOption = tile.m_eOption;
	m_pOptionTex = tile.m_pOptionTex;

	if (m_pOptionTex)
		m_pOptionTex->AddRef();
}


CTile::~CTile() {
	SAFE_RELEASE(m_pOptionTex);
}

void CTile::SetTileOption(TILE_OPTION eOption) {
	m_eOption = eOption;
	SAFE_RELEASE(m_pOptionTex);

	switch (eOption) {
	case TO_NONE:
		m_pOptionTex = GET_SINGLE(CResourceManager)->FindTexture("TileNone");
		break;
	case TO_NOMOVE:
		m_pOptionTex = GET_SINGLE(CResourceManager)->FindTexture("TileNoMove");
		break;
	}
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
	POSITION tPos = m_tPos - m_tSize * m_tPivot;
	tPos -= GET_SINGLE(CCamera)->GetPos();

	RESOLUTION tClientRS = GET_SINGLE(CCamera)->GetClientRS();

	bool bInClient = true;

	if (tPos.x + m_tSize.x < 0)
		bInClient = false;
	else if (tPos.x > tClientRS.iW)
		bInClient = false;
	else if (tPos.y + m_tSize.y < 0)
		bInClient = false;
	else if (tPos.y > tClientRS.iH)
		bInClient = false;

	if (m_pTexture && bInClient) {
		POSITION tImagePos;

		tImagePos += m_tImageOffset;

		if (m_pOptionTex->GetColorKeyEnable()) {
			TransparentBlt(hDC, tPos.x, tPos.y, m_tSize.x, m_tSize.y, m_pOptionTex->GetDC(),
				tImagePos.x, tImagePos.y, m_tSize.x, m_tSize.y, m_pTexture->GetColorKey());
		}
		else {
			BitBlt(hDC, tPos.x, tPos.y, m_tSize.x, m_tSize.y, m_pOptionTex->GetDC(), 0, 0, SRCCOPY);
		}
	}
}

CTile * CTile::Clone() {
	return new CTile(*this);
}

void CTile::Save(FILE * pFile) {
	CStaticObj::Save(pFile);
	fwrite(&m_eOption, 4, 1, pFile);
}

void CTile::Load(FILE * pFile) {
	CStaticObj::Load(pFile);
	fread(&m_eOption, 4, 1, pFile);
}
