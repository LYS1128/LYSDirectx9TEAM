#pragma once

#pragma warning (disable : 4005)
#pragma warning (disable : 4251)

#include <d3d9.h>
#include <d3dx9.h>

#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>

#include <time.h>

#include "Engine_Struct.h"
#include "Engine_Macro.h"
#include "Engine_Function.h"
#include "Engine_Typedef.h"

#include <vector>
#include <map>
#include <list>
#include <unordered_map>
#include <algorithm>
using namespace std;

#define G 9.8f
#define VK_MAX 0xff

#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW 
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW		
#endif 
#endif

using namespace Engine;