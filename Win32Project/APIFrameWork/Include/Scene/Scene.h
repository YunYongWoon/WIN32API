#pragma once

#include "../Game.h"

class CScene
{
private:
	friend class CSceneManager;
protected:
	CScene();
	virtual ~CScene() = 0;

public:
	virtual bool Init();
};

