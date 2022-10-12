#include "stdafx.h"
#include "..\Public\Dark_Effect.h"


CDark_Effect::CDark_Effect(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CUI(pGraphic_Device)
{
}

CDark_Effect::CDark_Effect(const CDark_Effect & rhs)
	: CUI(rhs)
{
}

HRESULT CDark_Effect::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CDark_Effect : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CDark_Effect::NativeConstruct(void* pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CDark_Effect : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CDark_Effect : NativeConstruct");
		return E_FAIL;
	}
	m_tUIInfo.fCX = g_iWinCX;
	m_tUIInfo.fCY = g_iWinCY;
	m_tUIInfo.fX = g_iWinCX * 0.5f;
	m_tUIInfo.fY = g_iWinCY * 0.5f;

	m_pUltimate = (CUI*)pArg;

	m_fZDis = 1.f;

	return S_OK;
}

void CDark_Effect::Tick(_float fTimeDelta) {
	__super::Tick(fTimeDelta);
}

void CDark_Effect::LateTick(_float fTimeDelta) {
	__super::LateTick(fTimeDelta);
	if (STATE_DEAD == m_pUltimate->Get_State()) {
		m_eState = STATE_DEAD;
	}
}

HRESULT CDark_Effect::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CDark_Effect : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CDark_Effect::SetUp_Components() {
	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform))) {
		MSG_BOX(L"Failed To CDark_Effect : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Effect_Dark"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CDark_Effect : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CDark_Effect : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CDark_Effect : SetUp_Components");
		return E_FAIL;
	}

	return S_OK;
}

CDark_Effect * CDark_Effect::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CDark_Effect* pInstance = new CDark_Effect(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CDark_Effect : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CDark_Effect::Clone(void * pArg) {
	CDark_Effect* pInstance = new CDark_Effect(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CDark_Effect : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CDark_Effect::Free() {
	__super::Free();
}
