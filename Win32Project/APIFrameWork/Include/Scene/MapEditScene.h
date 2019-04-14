#pragma once
#include "Scene.h"
class CMapEditScene :
	public CScene {
private:
	friend class CSceneManager;

private:
	CMapEditScene();
	~CMapEditScene();

public:
	virtual bool Init();
};

