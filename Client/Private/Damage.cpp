#include "stdafx.h"
#include "..\Public\Damage.h"

CDamage::CDamage(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CUI(pGraphic_Device)
{
}

CDamage::CDamage(const CDamage& rhs)
	: CUI(rhs)
{
}

HRESULT CDamage::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CDamage : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CDamage::NativeConstruct(void* pArg) {
	if (nullptr == pArg) {
		MSG_BOX(L"Failed To CDamage : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CDamage : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CDamage : NativeConstruct");
		return E_FAIL;
	}

	m_tDamage.chDamageID = ((DAMAGE*)pArg)->chDamageID;
	m_tDamage.eDamageType = ((DAMAGE*)pArg)->eDamageType;

	m_tUIInfo.fCX = 60.f;
	m_tUIInfo.fCY = 90.f;
	m_tUIInfo.fX = ((DAMAGE*)pArg)->fX;
	m_tUIInfo.fY = ((DAMAGE*)pArg)->fY;

	m_iUIType = UI_DAMAGE;

	return S_OK;
}

void CDamage::Tick(_float fTimeDelta) {
	__super::Tick(fTimeDelta);
	if (DAMAGE_PLAYER == m_tDamage.eDamageType) {
		Safe_Release(m_pTexture);
		m_pTexture = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Damage", L"Com_Texture_Damage_검은사슬");
		Safe_AddRef(m_pTexture);
	}
	else if (DAMAGE_MONSTER == m_tDamage.eDamageType) {
		Safe_Release(m_pTexture);
		m_pTexture = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Damage", L"Com_Texture_Damage_종이접기");
		Safe_AddRef(m_pTexture);
	}

	if ('0' == m_tDamage.chDamageID) {
		m_iSprite = 0;
	}
	else if ('1' == m_tDamage.chDamageID) {
		m_iSprite = 1;
	}
	else if ('2' == m_tDamage.chDamageID) {
		m_iSprite = 2;
	}
	else if ('3' == m_tDamage.chDamageID) {
		m_iSprite = 3;
	}
	else if ('4' == m_tDamage.chDamageID) {
		m_iSprite = 4;
	}
	else if ('5' == m_tDamage.chDamageID) {
		m_iSprite = 5;
	}
	else if ('6' == m_tDamage.chDamageID) {
		m_iSprite = 6;
	}
	else if ('7' == m_tDamage.chDamageID) {
		m_iSprite = 7;
	}
	else if ('8' == m_tDamage.chDamageID) {
		m_iSprite = 8;
	}
	else if ('9' == m_tDamage.chDamageID) {
		m_iSprite = 9;
	}
}

void CDamage::LateTick(_float fTimeDelta) {
	__super::LateTick(fTimeDelta);
	++m_iTick;
	if (50 <= m_iTick) {
		m_eState = STATE_DEAD;
	}
	m_tUIInfo.fY -= 1.f;
}

HRESULT CDamage::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CDamage : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CDamage::SetUp_Components() {
	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform))) {
		MSG_BOX(L"Failed To CDamage : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Damage_종이접기"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_종이접기"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CDamage : SetUp_Components");
		return E_FAIL;
	}
	Safe_Release(m_pTexture);
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Damage_검은사슬"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_검은사슬"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CDamage : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CDamage : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CDamage : SetUp_Components");
		return E_FAIL;
	}

	return S_OK;
}

CDamage* CDamage::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CDamage* pInstance = new CDamage(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CDamage : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CDamage::Clone(void* pArg) {
	CDamage* pInstance = new CDamage(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CDamage : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CDamage::Free() {
	__super::Free();
}