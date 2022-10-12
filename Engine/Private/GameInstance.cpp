#include "..\Public\GameInstance.h"

IMPLEMENT_SINGLETON(CGameInstance)

CGameInstance::CGameInstance()
	:m_pGraphic_Device(CGraphic_Device::GetInstance())
	,m_pInput_Device(CInput_Device::GetInstance())
	,m_pMouse(CMouse::GetInstance())
	,m_pTimer_Manager(CTimer_Manager::GetInstance())
	,m_pLevel_Manager(CLevel_Manager::GetInstance())
	,m_pObject_Manager(CObject_Manager::GetInstance())
	,m_pComponent_Manager(CComponent_Manager::GetInstance())
	,m_pKey_Manager(CKey_Manager::GetInstance())
	,m_pFrustum(CFrustum::GetInstance())
{
	Safe_AddRef(m_pGraphic_Device);
	Safe_AddRef(m_pInput_Device);
	Safe_AddRef(m_pMouse);
	Safe_AddRef(m_pTimer_Manager);
	Safe_AddRef(m_pLevel_Manager);
	Safe_AddRef(m_pObject_Manager);
	Safe_AddRef(m_pComponent_Manager);
	Safe_AddRef(m_pKey_Manager);
	Safe_AddRef(m_pFrustum);
}

HRESULT CGameInstance::Initialize_Engine(HINSTANCE hInst, _uint LvCnt, CGraphic_Device::INITENGINE InitEngine, LPDIRECT3DDEVICE9* ppGraphic_Device) {
	if (nullptr == m_pGraphic_Device || nullptr == m_pInput_Device) {
		MSG_BOX(L"Failed To CGameInstance : Initialize_Engine");
		return E_FAIL;
	}
	if (FAILED(m_pGraphic_Device->InitDevice(InitEngine.hWnd, InitEngine.iWinCX, InitEngine.iWinCY, ppGraphic_Device))) {
		MSG_BOX(L"Failed To CGameInstance : Initialize_Engine");
		return E_FAIL;
	}
	if (FAILED(m_pInput_Device->InitDevice(hInst, InitEngine.hWnd))) {
		MSG_BOX(L"Failed To CGameInstance : Initialize_Engine");
		return E_FAIL;
	}
	if (FAILED(m_pObject_Manager->Reserve_Manager(LvCnt))) {
		MSG_BOX(L"Failed To CGameInstance : Initialize_Engine");
		return E_FAIL;
	}
	if (FAILED(m_pComponent_Manager->Reserve_Manager(LvCnt))) {
		MSG_BOX(L"Failed To CGameInstance : Initialize_Engine");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CGameInstance::Initialize_Engine_Tool(_uint LvCnt, CGraphic_Device::INITENGINE InitEngine, LPDIRECT3DDEVICE9* ppGraphic_Device) {
	if (nullptr == m_pGraphic_Device) {
		MSG_BOX(L"Failed To CGameInstance : Initialize_Engine");
		return E_FAIL;
	}
	if (FAILED(m_pGraphic_Device->InitDevice(InitEngine.hWnd, InitEngine.iWinCX, InitEngine.iWinCY, ppGraphic_Device))) {
		MSG_BOX(L"Failed To CGameInstance : Initialize_Engine");
		return E_FAIL;
	}
	if (FAILED(m_pObject_Manager->Reserve_Manager(LvCnt))) {
		MSG_BOX(L"Failed To CGameInstance : Initialize_Engine");
		return E_FAIL;
	}
	if (FAILED(m_pComponent_Manager->Reserve_Manager(LvCnt))) {
		MSG_BOX(L"Failed To CGameInstance : Initialize_Engine");
		return E_FAIL;
	}
	return S_OK;
}

void CGameInstance::Tick_Engine(_float fTimeDelta) {
	if (nullptr == m_pLevel_Manager ||
		nullptr == m_pInput_Device ||
		nullptr == m_pFrustum)
		return;

	m_pInput_Device->SetUp_InputDeviceState();

	m_pObject_Manager->Tick(fTimeDelta);

	m_pFrustum->Tick(m_pGraphic_Device->Get_Device(),fTimeDelta);
	m_pObject_Manager->LateTick(fTimeDelta);


	m_pLevel_Manager->Tick(fTimeDelta);
}

HRESULT CGameInstance::Render_Engine() {
	if (nullptr == m_pGraphic_Device) {
		MSG_BOX(L"Failed To CGameInstance : Render_Engine");
		return E_FAIL;
	}
	m_pLevel_Manager->Render();
	return S_OK;
}

HRESULT CGameInstance::Render_Begin() {
	if (nullptr == m_pGraphic_Device) {
		MSG_BOX(L"Failed To CGameInstance : Render_Begin");
		return E_FAIL;
	}
	m_pGraphic_Device->Render_Begin();
	return S_OK;
}

HRESULT CGameInstance::Render_End() {
	if (nullptr == m_pGraphic_Device) {
		MSG_BOX(L"Failed To CGameInstance : Render_End");
		return E_FAIL;
	}
	m_pGraphic_Device->Render_End();
	return S_OK;
}

LPD3DXSPRITE CGameInstance::Get_Sprite() {
	if (nullptr == m_pGraphic_Device) {
		MSG_BOX(L"Failed To CGameInstance : Get_Font");
		return nullptr;
	}
	return m_pGraphic_Device->Get_Sprite();
}

LPD3DXFONT CGameInstance::Get_Font() {
	if (nullptr == m_pGraphic_Device) {
		MSG_BOX(L"Failed To CGameInstance : Get_Font");
		return nullptr;
	}
	return m_pGraphic_Device->Get_Font();
}

_char CGameInstance::Get_DIKeyState(_uchar byKeyID) {
	if (nullptr == m_pInput_Device) {
		return 0;
	}
	return m_pInput_Device->Get_DIKeyState(byKeyID);
}

_char CGameInstance::Get_DIMButtonState(CInput_Device::MOUSEBUTTONSTATE eDIMBState) {
	if (nullptr == m_pInput_Device) {
		return 0;
	}
	return m_pInput_Device->Get_DIMButtonState(eDIMBState);
}

_long CGameInstance::Get_DIMMoveState(CInput_Device::MOUSEMOVESTATE eDIMMState) {
	if (nullptr == m_pInput_Device) {
		return 0;
	}
	return m_pInput_Device->Get_DIMMoveState(eDIMMState);
}

_bool CGameInstance::Key_Pressing(_uint iKey) {
	if (nullptr == m_pKey_Manager) {
		return 0;
	}
	return m_pKey_Manager->Key_Pressing(iKey);
}

_bool CGameInstance::Key_Down(_uint iKey) {
	if (nullptr == m_pKey_Manager) {
		return 0;
	}
	return m_pKey_Manager->Key_Down(iKey);
}

_bool CGameInstance::Key_Up(_uint iKey) {
	if (nullptr == m_pKey_Manager) {
		return 0;
	}
	return m_pKey_Manager->Key_Up(iKey);
}

CMouse::RAY CGameInstance::Make_Ray(HWND hWnd, int iWinCX, int iWinCY) {
	return m_pMouse->Make_Ray(hWnd, iWinCX, iWinCY);;
}

CMouse::PICK* CGameInstance::Picking_Cube(VTXCUBETEX* pVertices, _float4x4 WorldMatrix) {
	return  m_pMouse->Picking_Cube(pVertices, WorldMatrix);
}

HRESULT CGameInstance::Set_Graphic_Device(LPDIRECT3DDEVICE9 pGraphic_Device) {
	if (nullptr == m_pMouse) {
		MSG_BOX(L"Failed To CGameInstance : Set_Graphic_Device");
		return E_FAIL;
	}
	m_pMouse->Set_Graphic_Device(pGraphic_Device);
	return S_OK;
}

HRESULT CGameInstance::Add_Timers(const _tchar* pTimerTag) {
	if (nullptr == m_pTimer_Manager) {
		MSG_BOX(L"Failed To CGameInstance : Add_Timers");
		return E_FAIL;
	}
	m_pTimer_Manager->Add_Timers(pTimerTag);
	return S_OK;
}

_double CGameInstance::Compute_TimeDelta(const _tchar* pTimerTag) {
	if (nullptr == m_pTimer_Manager) {
		MSG_BOX(L"Failed To CGameInstance : Compute_TimeDelta");
		return E_FAIL;
	}
	return m_pTimer_Manager->Compute_TimeDelta(pTimerTag);
}

HRESULT CGameInstance::OpenLevel(_uint iLevelIndex, CLevel* pLevel) {	
	if (nullptr == m_pLevel_Manager) {
		MSG_BOX(L"Failed To CGameInstance : OpenLevel");
		return E_FAIL;
	}
	if (FAILED(m_pLevel_Manager->OpenLevel(iLevelIndex, pLevel))) {
		MSG_BOX(L"Failed To CGameInstance : OpenLevel");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CGameInstance::Add_Prototype(const _tchar * pPrototypeTag, CGameObject * pPrototype)
{
	if (nullptr == m_pObject_Manager)
		return E_FAIL;

	return m_pObject_Manager->Add_Prototype(pPrototypeTag, pPrototype);
}

HRESULT CGameInstance::Add_GameObjectToLayer(_uint iLevelIndex, const _tchar* pLayerTag, const _tchar* pPrototypeTag, void* pArg) {
	if (nullptr == m_pObject_Manager) {
		MSG_BOX(L"Failed To CGameInstance : Add_GameObjectToLayer");
		return E_FAIL;
	}
	m_pObject_Manager->Add_GameObjectToLayer(iLevelIndex, pLayerTag, pPrototypeTag, pArg);
	return S_OK;
}

CLayer* CGameInstance::Find_Layer(_uint iLevelIndex, const _tchar* pLayerTag) {
	if (nullptr == m_pObject_Manager) {
		MSG_BOX(L"Failed To CGameInstance : Find_Layer");
		return nullptr;
	}
	return m_pObject_Manager->Find_Layer(iLevelIndex, pLayerTag);
}

list<CGameObject*>* CGameInstance::Find_Layer_List(_uint iLevelIndex, const _tchar * pLayerTag)
{
	if (nullptr == m_pObject_Manager) {
		MSG_BOX(L"Failed To CGameInstance : Find_Layer_List");
		return nullptr;
	}
	return m_pObject_Manager->Find_Layer_List(iLevelIndex, pLayerTag);
}

CComponent* CGameInstance::Get_Component(_uint iLevelIndex, const _tchar* pLayerTag, const _tchar* pComponentTag, _uint iIndex) {
	if (nullptr == m_pObject_Manager) {
		MSG_BOX(L"Failed To CGameInstance : Get_Component");
		return nullptr;
	}
	return m_pObject_Manager->Get_Component(iLevelIndex, pLayerTag, pComponentTag, iIndex);
}

HRESULT CGameInstance::Add_Prototype(_uint iLevelIndex, const _tchar* pPrototypeTag, CComponent* pPrototype) {
	if (nullptr == m_pComponent_Manager) {
		MSG_BOX(L"Failed To CGameInstance : Add_Prototype");
		return E_FAIL;
	}
	return m_pComponent_Manager->Add_Prototype(iLevelIndex, pPrototypeTag, pPrototype);
}

CComponent* CGameInstance::Clone_Component(_uint iLevelIndex, const _tchar* pPrototypeTag, void* pArg) {
	if (nullptr == m_pComponent_Manager) {
		return nullptr;
	}
	return m_pComponent_Manager->Clone_Component(iLevelIndex, pPrototypeTag, pArg);
}

_bool CGameInstance::Check_InOut(_float3 vPos, _float fRadius)
{
	if (nullptr == m_pFrustum) {
		return false;
	}
	return m_pFrustum->Check_InOut(vPos, fRadius);
}


void CGameInstance::Release_Engine() {
	CGameInstance::GetInstance()->DestroyInstance();
	CMouse::GetInstance()->DestroyInstance();
	CLevel_Manager::GetInstance()->DestroyInstance();
	CObject_Manager::GetInstance()->DestroyInstance();
	CComponent_Manager::GetInstance()->DestroyInstance();
	CTimer_Manager::GetInstance()->DestroyInstance();
	CKey_Manager::GetInstance()->DestroyInstance();
	CFrustum::GetInstance()->DestroyInstance();
	CInput_Device::GetInstance()->DestroyInstance();
	CGraphic_Device::GetInstance()->DestroyInstance();
	
}

void CGameInstance::Free() {
	Safe_Release(m_pMouse);
	Safe_Release(m_pTimer_Manager);
	Safe_Release(m_pLevel_Manager);
	Safe_Release(m_pObject_Manager);
	Safe_Release(m_pComponent_Manager);
	Safe_Release(m_pKey_Manager);
	Safe_Release(m_pFrustum);
	Safe_Release(m_pInput_Device);
	Safe_Release(m_pGraphic_Device);
}