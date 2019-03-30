#pragma once

#include <Windows.h>
#include <list>
#include <vector>
#include <unordered_map>
#include <crtdbg.h>
#include <typeinfo>
#include <string>
#include <functional>

#pragma comment(lib,"msimg32")

using namespace std;

#include "resource.h"
#include "Macro.h"
#include "Type.h"
#include "Flag.h"

#define PI 3.141592f

// PATH Key
#define ROOT_PATH		"RootPath"
#define TEXTURE_PATH	"TexturePath"

template <typename T>
void Safe_Delete_VecList(T& p) {
	T::iterator iter;
	T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; iter++) {
		SAFE_DELETE((*iter));
	}

	p.clear();
}

template <typename T>
void Safe_Release_VecList(T& p) {
	T::iterator iter;
	T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; iter++) {
		SAFE_RELEASE((*iter));
	}

	p.clear();
}

template <typename T>
void Safe_Release_Map(T& p) {
	T::iterator iter;
	T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; iter++) {
		SAFE_RELEASE(iter->second);
	}

	p.clear();
}

template <typename T>
void Safe_Delete_Map(T& p) {
	T::iterator iter;
	T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; iter++) {
		SAFE_DELETE(iter->second);
	}

	p.clear();
}