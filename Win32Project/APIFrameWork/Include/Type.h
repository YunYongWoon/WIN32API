#pragma once
typedef struct _tagResolution {
	unsigned int iW;
	unsigned int iH;

	_tagResolution() :iW(0), iH(0) {

	}

	_tagResolution(int x, int y) :iW(x), iH(y) {

	}
}RESOLUTION, *PRESOLUTION;

typedef struct _tagPosition {
	float x, y;

	_tagPosition() :
		x(0.f), y(0.f) {

	}

	_tagPosition(float _x, float _y) :
		x(_x), y(_y) {

	}

	_tagPosition(const _tagPosition& pos){
		x = pos.x;
		y = pos.y;
	}

	_tagPosition(const POINT& pt) {
		x = pt.x;
		y = pt.y;
	}

	void operator =(const _tagPosition & pos) {
		x = pos.x;
		y = pos.y;
	}

	void operator =(const POINT& pt) {
		x = pt.x;
		y = pt.y;
	}

	void operator =(float f[2]) {
		x = f[0];
		y = f[1];
	}
// ----------------------- 더하기-------------------
	_tagPosition operator + (const _tagPosition& pos) const {
		_tagPosition tPos;
		tPos.x = x + pos.x;
		tPos.y = y + pos.y;
		return tPos;
	}

	_tagPosition operator + (const POINT& pos) const {
		_tagPosition tPos;
		tPos.x = x + pos.x;
		tPos.y = y + pos.y;
		return tPos;
	}

	_tagPosition operator + (float f[2]) const {
		_tagPosition tPos;
		tPos.x = x + f[0];
		tPos.y = y + f[1];
		return tPos;
	}

	_tagPosition operator + (float f) const {
		_tagPosition tPos;
		tPos.x = x + f;
		tPos.y = y + f;
		return tPos;
	}

	void operator +=(const _tagPosition& pos) {
		x += pos.x;
		y += pos.y;
	}


// ---------------------- 빼기 ---------------------
	_tagPosition operator - (const _tagPosition& pos) const {
		_tagPosition tPos;
		tPos.x = x - pos.x;
		tPos.y = y - pos.y;
		return tPos;
	}

	_tagPosition operator - (const POINT& pos) const {
		_tagPosition tPos;
		tPos.x = x - pos.x;
		tPos.y = y - pos.y;
		return tPos;
	}

	_tagPosition operator - (float f[2]) const {
		_tagPosition tPos;
		tPos.x = x - f[0];
		tPos.y = y - f[1];
		return tPos;
	}

	_tagPosition operator - (float f) const {
		_tagPosition tPos;
		tPos.x = x - f;
		tPos.y = y - f;
		return tPos;
	}

	void operator -=(const _tagPosition& pos) {
		x -= pos.x;
		y -= pos.y;
	}

// ---------------------- 곱하기 ---------------------
	_tagPosition operator * (const _tagPosition& pos) {
		_tagPosition tPos;
		tPos.x = x * pos.x;
		tPos.y = y * pos.y;
		return tPos;
	}

	_tagPosition operator * (const POINT& pos) {
		_tagPosition tPos;
		tPos.x = x * pos.x;
		tPos.y = y * pos.y;
		return tPos;
	}

	_tagPosition operator * (float f[2]) {
		_tagPosition tPos;
		tPos.x = x * f[0];
		tPos.y = y * f[1];
		return tPos;
	}

	_tagPosition operator * (float f) const {
		_tagPosition tPos;
		tPos.x = x * f;
		tPos.y = y * f;
		return tPos;
	}

// ---------------------- 나누기 ---------------------
	_tagPosition operator / (const _tagPosition& pos) {
		_tagPosition tPos;
		tPos.x = x / pos.x;
		tPos.y = y / pos.y;
		return tPos;
	}

	_tagPosition operator / (const POINT& pos) {
		_tagPosition tPos;
		tPos.x = x / pos.x;
		tPos.y = y / pos.y;
		return tPos;
	}

	_tagPosition operator / (float f[2]) {
		_tagPosition tPos;
		tPos.x = x / f[0];
		tPos.y = y / f[1];
		return tPos;
	}

	_tagPosition operator / (float f) {
		_tagPosition tPos;
		tPos.x = x / f;
		tPos.y = y / f;
		return tPos;
	}

}POSITION, *PPOSITION, _SIZE, *_PSIZE;