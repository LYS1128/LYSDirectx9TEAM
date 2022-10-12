#include "stdafx.h"
#include "..\Public\Level_Logo.h"

CLevel_Logo::CLevel_Logo(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CLevel(pGraphic_Device)
{
}

HRESULT CLevel_Logo::NativeConstruct() {
	if (FAILED(Ready_Logo())) {
		MSG_BOX(L"Failed To CLevel_Logo : NativeConstruct");
		return E_FAIL;
	}
	return S_OK;
}

void CLevel_Logo::Tick(_float fTimeDelta) {
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (pGameInstance->Key_Down(VK_RETURN)) {
		if (FAILED(pGameInstance->OpenLevel(LEVEL_LOADING, CLevel_Loading::Create(m_pGraphic_Device, LEVEL_TUTORIAL)))) {
			return;
		}
	}
	Safe_Release(pGameInstance);
}

HRESULT CLevel_Logo::Render() {
	if (FAILED(__super::Render()))
		return E_FAIL;

	SetWindowText(g_hWnd, TEXT("로고레벨입니다."));

	return S_OK;
}

HRESULT CLevel_Logo::Ready_Logo() {
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LOGO, TEXT("Layer_UI"), TEXT("Prototype_GameObject_UI")))) {
		MSG_BOX(L"Failed To CLevel_Logo : Ready_Layer_UI");
		return E_FAIL;
	}

	Safe_Release(pGameInstance);
	return S_OK;
}

CLevel_Logo* CLevel_Logo::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CLevel_Logo* pInstance = new CLevel_Logo(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct())) {
		MSG_BOX(L"Failed To CLevel_Logo : Create");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLevel_Logo::Free()
{
	__super::Free();
}