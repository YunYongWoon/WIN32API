#pragma once
#include "StaticObj.h"
class CTile :
	public CStaticObj {
private:
	friend class CObj;
	friend class CStage;

public:
	CTile();
	CTile(const CTile& tile);
	~CTile();

private:
	TILE_OPTION m_eOption;
	class CTexture* m_pOptionTex;

public:
	void SetTileOption(TILE_OPTION eOption);

	TILE_OPTION GetTileOption() const {
		return m_eOption;
	}

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CTile* Clone();
	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);
};

