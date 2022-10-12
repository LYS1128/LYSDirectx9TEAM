#include "stdafx.h"
#include "..\Public\BossRealHp.h"

CBossRealHp::CBossRealHp(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CUI(pGraphic_Device)
{
}

CBossRealHp::CBossRealHp(const CBossRealHp & rhs)
	:CUI(rhs)
{
}

HRESULT CBossRealHp::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CBossRealHp : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CBossRealHp::NativeConstruct(void* pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CBossRealHp : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CBossRealHp : NativeConstruct");
		return E_FAIL;
	}

	m_pTargetMonster = ((CMonster*)pArg);

	m_fOriginScaleX = g_iWinCX * 0.7f - 112.f;

	m_tUIInfo.fCX = g_iWinCX * 0.7f - 112.f;
	m_tUIInfo.fCY = 22.f;
	m_tUIInfo.fY = 71.f;

	m_iUIType = UI_DAMAGE;

	return S_OK;
}

void CBossRealHp::Tick(_float fTimeDelta) {
	__super::Tick(fTimeDelta);
	_uint iHp = m_pTargetMonster->Get_Monster_Info().iHp;
	_uint iMaxHp = m_pTargetMonster->Get_Monster_Info().iMaxHp;

	_float fPercentage = (_float)iHp / iMaxHp;
	
	m_tUIInfo.fCX = m_fOriginScaleX * fPercentage;
	m_tUIInfo.fX = (g_iWinCX * 0.5f + 43.f) - (m_fOriginScaleX - m_tUIInfo.fCX) * 0.5f;
}

void CBossRealHp::LateTick(_float fTimeDelta) {
	__super::LateTick(fTimeDelta);
}

HRESULT CBossRealHp::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBossRealHp : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CBossRealHp::SetUp_Components() {
	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform))) {
		MSG_BOX(L"Failed To CBossRealHp : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_MonsterRealHp"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CBossRealHp : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CBossRealHp : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CBossRealHp : SetUp_Components");
		return E_FAIL;
	}

	return S_OK;
}

CBossRealHp* CBossRealHp::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CBossRealHp* pInstance = new CBossRealHp(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CBossRealHp : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CBossRealHp::Clone(void * pArg) {
	CBossRealHp* pInstance = new CBossRealHp(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CBossRealHp : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CBossRealHp::Free() {
	__super::Free();
}