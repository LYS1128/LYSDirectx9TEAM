#include "stdafx.h"
#include "..\Public\Claw_Attack.h"

CClaw_Attack::CClaw_Attack(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CBoss_Skill(pGraphic_Device)
{
}

CClaw_Attack::CClaw_Attack(const CClaw_Attack & rhs)
	:CBoss_Skill(rhs)
{
}

HRESULT CClaw_Attack::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CClaw_Attack : NativeConstruct_Prototype");
		return E_FAIL;
	}
	m_iDamagePercent = 2;
	return S_OK;
}

HRESULT CClaw_Attack::NativeConstruct(void * pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CClaw_Attack : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CClaw_Attack : NativeConstruct");
		return E_FAIL;
	}
	m_eSkill = SKILL_CLAW;

	m_tBossSkillFrame.fFrame = 0.f;
	m_tBossSkillFrame.iSpriteEnd = 4;

	_float3 vPos = *((_float3*)pArg);
	m_pTransform->Set_State(CTransform::STATE_POSITION, vPos - _float3(0.f, 1.0f, 0.f));
	m_pTransform->Scaled(_float3(4.f, 3.5f, 1.f));

	return S_OK;
}

void CClaw_Attack::Tick(_float fTimeDelta) {
	__super::Tick(fTimeDelta);
}

void CClaw_Attack::LateTick(_float fTimeDelta) {
	__super::LateTick(fTimeDelta);
}

HRESULT CClaw_Attack::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CClaw_Attack : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CClaw_Attack::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 1.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CBoss_Phase1 : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Boss_Claw_Attack"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CBoss_Phase1 : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CBoss_Phase1 : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CBoss_Phase1 : SetUp_Components");
		return E_FAIL;
	}
	return S_OK;
}

CClaw_Attack * CClaw_Attack::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CClaw_Attack* pInstance = new CClaw_Attack(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CClaw_Attack : Create");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CClaw_Attack::Clone(void * pArg) {
	CClaw_Attack* pInstance = new CClaw_Attack(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CClaw_Attack : Clone");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CClaw_Attack::Free() {
	__super::Free();
}