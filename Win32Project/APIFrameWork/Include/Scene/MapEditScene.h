#pragma once
#include "Scene.h"

class CMapEditScene :
	public CScene {
private:
	friend class CSceneManager;

private:
	CMapEditScene();
	~CMapEditScene();

private:
	TILE_EDIT_MODE m_eTem;
	TILE_OPTION	m_eEditOption;
	vector<class CTexture*> m_vecTileTex;
	class CStage* m_pStage;
	int m_iEditTileTex;

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
};

