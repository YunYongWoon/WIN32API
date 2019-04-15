#pragma once
#include "StaticObj.h"
class CStage :
	public CStaticObj
{
private:
	friend class CObj;
	friend class CScene;

public:
	CStage();
	CStage(const CStage& stage);
	~CStage();

private:
	vector<class CTile*> m_vecTile;
	int m_iTileNumX;
	int m_iTileNumY;
	int m_iTileSizeX;
	int m_iTileSizeY;

public:
	void CreateTile(int iNumX, int iNumY, int iSizeX, int iSizeY,
		const string& strKey = "", const wchar_t* pFileName = NULL,
		const string& strPathKey = TEXTURE_PATH);

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CStage* Clone();
	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);

public:
	void ChangeTileTexture(const POSITION& tPos,
		class CTexture* pTexture);
	void ChangeTileOption(const POSITION& tPos,
		TILE_OPTION eOption);
	int GetTileIndex(const POSITION& tPos);
	int GetTileIndex(float x, float y);
};

