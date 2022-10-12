#include "stdafx.h"
#include "..\Public\Electric_Shock.h"

CElectric_Shock::CElectric_Shock(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CBoss_Skill(pGraphic_Device)
{
}

CElectric_Shock::CElectric_Shock(const CElectric_Shock & rhs)
	: CBoss_Skill(rhs)
{
}

HRESULT CElectric_Shock::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CElectric_Shock : NativeConstruct_Prototype");
		return E_FAIL;
	}
	
	m_iDamagePercent = 1;
	m_iDamage = 1;
	return S_OK;
}

HRESULT CElectric_Shock::NativeConstruct(void* pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CElectric_Shock : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CElectric_Shock : NativeConstruct");
		return E_FAIL;
	}

	m_eSkill = SKILL_ELECTRIC;

	m_tBossSkillFrame.fFrame = 0.f;
	m_tBossSkillFrame.iSpriteEnd = 9;

	_float3 PlayerPos = dynamic_cast<CTransform*>(m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform"))->Get_State(CTransform::STATE_POSITION);
	m_pTransform->Set_State(CTransform::STATE_POSITION, PlayerPos);

	m_pTransform->Scaled(_float3(1.01f, 1.51f, 1.01f));

	return S_OK;
}

void CElectric_Shock::Tick(_float fTimeDelta) {
	__super::Tick(fTimeDelta);

}

void CElectric_Shock::LateTick(_float fTimeDelta) {
	m_tBossSkillFrame.fFrame += m_tBossSkillFrame.iSpriteEnd * fTimeDelta;
	if ((_uint)m_tBossSkillFrame.fFrame >= m_tBossSkillFrame.iSpriteEnd) {
		m_tBossSkillFrame.fFrame = 3.f;
		++m_iTick;
	}
	if (1 <= m_iTick) {
		m_eState = STATE_DEAD;
	}
	m_pRenderer->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
}

HRESULT CElectric_Shock::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CElectric_Shock : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CElectric_Shock::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 1.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CElectric_Shock : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Electric_Shock"), LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Electric_Shock"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CElectric_Shock : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CElectric_Shock : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CElectric_Shock : SetUp_Components");
		return E_FAIL;
	}
	return S_OK;
}

CElectric_Shock* CElectric_Shock::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CElectric_Shock*	pInstance = new CElectric_Shock(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CElectric_Shock : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CElectric_Shock::Clone(void* pArg) {
	CElectric_Shock*	pInstance = new CElectric_Shock(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CElectric_Shock : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CElectric_Shock::Free() {
	__super::Free();
}