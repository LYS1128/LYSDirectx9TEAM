#pragma once
#include "Base.h"
#include "Client_Define.h"
//레벨
#include "Level_Logo.h"
//렌더러
#include "Renderer.h"
//게임 인스턴스
#include "GameInstance.h"
#include "Object_UI.h"
#include "Load_Spring.h"
#include "Sound_Manager.h"
#include "Text.h"
#include "Mouse_UI.h"
#include "Shader.h"
#include "NooNooAttack.h"



BEGIN(Client)

class CMainApp final : public CBase {
private:
	CMainApp();
	virtual ~CMainApp() = default;
public:
	HRESULT NativeConstruct();
	void Tick(_float fTimeDelta);
	HRESULT Render();
public:
	HRESULT OpenLevel(LEVEL eLevelIndex);
	HRESULT SetUp_Prototype_Component();
	HRESULT SetUp_RenderState();
	HRESULT Ready_Font();
private:
	CGameInstance* m_pGameInstance = nullptr;
	LPDIRECT3DDEVICE9 m_pGraphic_Device = nullptr;
	CRenderer* m_pRenderer = nullptr;
private:
	_uint m_iFPS = 0;
	DWORD m_dwTime;
	TCHAR	m_szFPS[32];
public:
	static CMainApp* Create();
	virtual void Free();
};

END