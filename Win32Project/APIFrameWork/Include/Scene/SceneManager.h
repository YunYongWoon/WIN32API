#pragma once

#include "../Game.h"

class CSceneManager {
	DECLARE_SINGLE(CSceneManager)

private:
	class CScene* m_pScene;
	class CScene* m_pNextScene;

public:
	template<typename T>
	T* CreateScene(SCENE_CREATE sc) {
		T* pScene = new T;
		if (!pScene->Init()) {
			SAFE_DELETE(pScene);
			return NULL;
		}

		switch (sc) {
		case SC_CURRENT:
			SAFE_DELETE(m_pScene);
			break;
		case SC_NEXT:
			SAFE_DELETE(m_pNextScene);
			m_pNextScene = pScene;
			break;
		}
		return pScene;
	}

	bool Init();
};

