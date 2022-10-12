#pragma once


namespace Client {
	const unsigned int g_iWinCX = 1280;
	const unsigned int g_iWinCY = 720;

	enum LEVEL {
		LEVEL_STATIC, LEVEL_LOGO, LEVEL_LOADING, LEVEL_TUTORIAL, LEVEL_STAGEONE, LEVEL_STAGETWO, LEVEL_STAGETWO_1,
		LEVEL_STAGETHREE, LEVEL_STAGEFOUR, LEVEL_STAGESEMIBOSS, LEVEL_STAGESEMIAFTER, LEVEL_STAGEFIVE, LEVEL_STAGESIX, LEVEL_STAGESEVEN,
		LEVEL_STAGEEIGHT, LEVEL_STAGEBOSS, LEVEL_STAGESPECIAL, LEVEL_END
	};

	enum SKILLID { SKILL_FREEZE, SKILL_CRAY, SKILL_ICE, SKILL_EARTHQUAKE, SKILL_MOONLIGHT, SKILL_END };


	typedef struct tagObjectInfo {
		int iHp;
		int iMp;
		int iMaxHp;
		int iMaxMp;
		unsigned int iLevel;
		unsigned int iExp;
		unsigned int iMaxExp;
		unsigned int iAtt;
		unsigned int iDef;
		unsigned int iGold;
	}INFO;
}

#define VOLUME 0.2f
#define VOLUME5 0.7f

#define LOADING 0 // defalut 3333333333

#include <process.h>

extern HWND g_hWnd;
extern HINSTANCE g_hInst;

extern unsigned int g_iLevel;

using namespace Client;

#include <tchar.h>
#include <string>

#include <io.h>
#include "fmod.h"
#include "fmod.hpp"
#include "fmod_errors.h"
using namespace FMOD;