#pragma once
#include "Scene.h"
class CStartScene :
	public CScene
{
private:
	friend class CSceneManager;

private:
	CStartScene();
	~CStartScene();

public:
	virtual bool Init();
};

