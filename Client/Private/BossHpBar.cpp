#include "stdafx.h"
#include "..\Public\BossHpBar.h"

CBossHpBar::CBossHpBar(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CUI(pGraphic_Device)
{
}

CBossHpBar::CBossHpBar(const CBossHpBar & rhs)
	:CUI(rhs)
{
}

HRESULT CBossHpBar::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CBossHpBar : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CBossHpBar::NativeConstruct(void * pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CBossHpBar : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CBossHpBar : NativeConstruct");
		return E_FAIL;
	}

	m_pTargetMonster = ((CMonster*)pArg);

	m_tUIInfo.fCX = g_iWinCX * 0.7f;
	m_tUIInfo.fCY = 50.f;
	m_tUIInfo.fX = g_iWinCX * 0.5f;
	m_tUIInfo.fY = 70.f;

	m_iUIType = UI_DAMAGE - 1;

	return S_OK;
}

void CBossHpBar::Tick(_float fTimeDelta) {
	__super::Tick(fTimeDelta);
	if (STATE_DEAD == m_pTargetMonster->Get_State()) {
		m_eState = STATE_DEAD;
	}
}

void CBossHpBar::LateTick(_float fTimeDelta) {
	__super::LateTick(fTimeDelta);
}

HRESULT CBossHpBar::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBossHpBar : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CBossHpBar::SetUp_Components() {
	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform))) {
		MSG_BOX(L"Failed To CBossHpBar : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_BossHpBar"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CBossHpBar : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CBossHpBar : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CBossHpBar : SetUp_Components");
		return E_FAIL;
	}

	return S_OK;
}

CBossHpBar* CBossHpBar::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CBossHpBar*	pInstance = new CBossHpBar(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CBossHpBar : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CBossHpBar::Clone(void* pArg) {
	CBossHpBar*	pInstance = new CBossHpBar(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CBossHpBar : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CBossHpBar::Free() {
	__super::Free();
}
