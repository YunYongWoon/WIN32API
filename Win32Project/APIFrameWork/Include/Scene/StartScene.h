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

public:
	void StartButtonCallback(float fTime);
	void EndButtonCallback(float fTime);
};

