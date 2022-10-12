#include "stdafx.h"
#include "..\Public\FPS.h"

CFPS::CFPS(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CUI(pGraphic_Device)
{
}

CFPS::CFPS(const CFPS & rhs)
	:CUI(rhs)
{
}

HRESULT CFPS::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CFPS : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CFPS::NativeConstruct(void * pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CMouse_UI : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CMouse_UI : NativeConstruct");
		return E_FAIL;
	}

	m_tUIInfo.fCX = 100.f;
	m_tUIInfo.fCY = 100.f;
	m_tUIInfo.fX = g_iWinCX * 0.5f;
	m_tUIInfo.fY = g_iWinCY * 0.5f;

	m_iUIType = UI_MOUSE;

	return S_OK;
}

void CFPS::Tick(_float fTimeDelta) {
	__super::Tick(fTimeDelta);
}

void CFPS::LateTick(_float fTimeDelta) {
	CMultiCamera* pCamera = (CMultiCamera*)(m_pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Camera")->front());
	Safe_AddRef(pCamera);

	if (nullptr == pCamera) {
		return;
	}
	if (3 == pCamera->Get_CameraMode()) {
		__super::LateTick(fTimeDelta);
	}
	Safe_Release(pCamera);
}

HRESULT CFPS::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CFPS : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CFPS::SetUp_Components() {
	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform))) {
		MSG_BOX(L"Failed To CFPS : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Mouse_UI"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Aim"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CFPS : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CFPS : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CFPS : SetUp_Components");
		return E_FAIL;
	}

	return S_OK;
}

CFPS * CFPS::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CFPS*	pInstance = new CFPS(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CFPS : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CFPS::Clone(void * pArg) {
	CFPS*	pInstance = new CFPS(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CFPS : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CFPS::Free() {
	__super::Free();
}