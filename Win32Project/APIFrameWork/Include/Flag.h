#pragma once
// Scene Type
enum SCENE_CREATE {
	SC_CURRENT,
	SC_NEXT
};

enum MOVE_DIR {
	MD_BACK = -1,
	MD_NONE,
	MD_FRONT
};

enum COLLIDER_TYPE {
	CT_RECT,
	CT_SPHERE,
	CT_LINE,
	CT_POINT,
	CT_PIXEL,
	CT_END
};