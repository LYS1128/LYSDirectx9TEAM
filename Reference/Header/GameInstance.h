#pragma once
#include "Base.h"
//디바이스
#include "Graphic_Device.h"
#include "Input_Device.h"
//마우스
#include "Mouse.h"
//매니저
#include "Timer_Manager.h"
#include "Level_Manager.h"
#include "Object_Manager.h"
#include "Component_Manager.h"
#include "Key_Manager.h"
#include "Frustum.h"

BEGIN(Engine)

class ENGINE_DLL CGameInstance final : public CBase {
	DECLARE_SINGLETON(CGameInstance)
private:
	CGameInstance();
	virtual ~CGameInstance() = default;
//엔진 프레임
public:
	HRESULT Initialize_Engine(HINSTANCE hInst, _uint iLvCnt, CGraphic_Device::INITENGINE InitEngine, LPDIRECT3DDEVICE9* ppGraphic_Device);
	HRESULT Initialize_Engine_Tool(_uint LvCnt, CGraphic_Device::INITENGINE InitEngine, LPDIRECT3DDEVICE9* ppGraphic_Device);
	void Tick_Engine(_float fTimeDelta);
	HRESULT Render_Engine();
	HRESULT Render_Begin();
	HRESULT Render_End();
//Graphic디바이스
	LPD3DXSPRITE Get_Sprite();
	LPD3DXFONT Get_Font();
//Input디바이스
	_char Get_DIKeyState(_uchar byKeyID);
	_char Get_DIMButtonState(CInput_Device::MOUSEBUTTONSTATE eDIMBState);
	_long Get_DIMMoveState(CInput_Device::MOUSEMOVESTATE eDIMMState);	
//Key_Manager
	_bool Key_Pressing(_uint iKey);
	_bool Key_Down(_uint iKey);
	_bool Key_Up(_uint iKey);
//마우스
	CMouse::RAY Make_Ray(HWND hWnd, int iWinCX, int iWinCY);
	CMouse::PICK* Picking_Cube(VTXCUBETEX* pVertices, _float4x4 WorldMatrix);
	HRESULT Set_Graphic_Device(LPDIRECT3DDEVICE9 pGraphic_Device);
//Timer_Manager
public:
	HRESULT Add_Timers(const _tchar* pTimerTag);
	_double Compute_TimeDelta(const _tchar* pTimerTag);
//Level_Manager
public:
	HRESULT OpenLevel(_uint iLevelIndex, CLevel* pLevel);
//Object_Manager
public:
	HRESULT Add_Prototype(const _tchar* pPrototypeTag, class CGameObject* pPrototype);
	HRESULT Add_GameObjectToLayer(_uint iLevelIndex, const _tchar* pLayerTag, const _tchar* pPrototypeTag, void* pArg = nullptr);
	CLayer* Find_Layer(_uint iLevelIndex, const _tchar* pLayerTag);
	list<CGameObject*>* Find_Layer_List(_uint iLevelIndex, const _tchar* pLayerTag);
	CComponent* Get_Component(_uint iLevelIndex, const _tchar* pLayerTag, const _tchar* pComponentTag, _uint iIndex = 0);
//Component_Manager
public:
	HRESULT Add_Prototype(_uint iLevelIndex, const _tchar* pPrototypeTag, CComponent* pPrototype);
	CComponent* Clone_Component(_uint iLevelIndex, const _tchar* pPrototypeTag, void* pArg);
//Frustum
	_bool Check_InOut(_float3 vPos, _float fRadius);

private:
	CGraphic_Device* m_pGraphic_Device = nullptr;
	CInput_Device* m_pInput_Device = nullptr;
	CMouse* m_pMouse = nullptr;
	CTimer_Manager* m_pTimer_Manager = nullptr;	
	CLevel_Manager* m_pLevel_Manager = nullptr;
	CObject_Manager* m_pObject_Manager = nullptr;
	CComponent_Manager* m_pComponent_Manager = nullptr;
	CKey_Manager* m_pKey_Manager = nullptr;
	CFrustum* m_pFrustum = nullptr;
public:
	static void Release_Engine();
	virtual void Free();
};

END