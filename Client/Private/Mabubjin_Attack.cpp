#include "stdafx.h"
#include "..\Public\Mabubjin_Attack.h"

CMabubjin_Attack::CMabubjin_Attack(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CBoss_Skill(pGraphic_Device)
{
}

CMabubjin_Attack::CMabubjin_Attack(const CMabubjin_Attack & rhs)
	:CBoss_Skill(rhs)
{
}

HRESULT CMabubjin_Attack::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CMabubjin_Attack : NativeConstruct_Prototype");
		return E_FAIL;
	}

	m_iDamagePercent = 3;
	return S_OK;
}

HRESULT CMabubjin_Attack::NativeConstruct(void * pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CMabubjin_Attack : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CMabubjin_Attack : NativeConstruct");
		return E_FAIL;
	}
	m_eSkill = SKILL_MABUBJIN;

	m_tBossSkillFrame.fFrame = 0.f;
	m_tBossSkillFrame.iSpriteEnd = 1;

	_float3 vPos = *((_float3*)pArg);
	m_pTransform->Set_State(CTransform::STATE_POSITION, vPos);

	m_pTransform->Set_State(CTransform::STATE_RIGHT, _float3(1.f, 0.f, 0.f));
	m_pTransform->Set_State(CTransform::STATE_UP, _float3(0.f, 0.f, -1.f));
	m_pTransform->Set_State(CTransform::STATE_LOOK, _float3(0.f, 1.f, 0.f));

	m_pTransform->Scaled(_float3(15.f, 15.f, 1.f));
	return S_OK;
}

void CMabubjin_Attack::Tick(_float fTimeDelta) {
	MoveFrame(fTimeDelta);
}

void CMabubjin_Attack::LateTick(_float fTimeDelta) {
	__super::LateTick(fTimeDelta);
}

HRESULT CMabubjin_Attack::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CMabubjin_Attack : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CMabubjin_Attack::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 1.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(10.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CMabubjin_Attack : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Boss_Mabubjin"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CMabubjin_Attack : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CMabubjin_Attack : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CMabubjin_Attack : SetUp_Components");
		return E_FAIL;
	}
	return S_OK;
}

CMabubjin_Attack * CMabubjin_Attack::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CMabubjin_Attack* pInstance = new CMabubjin_Attack(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CMabubjin_Attack : Create");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CMabubjin_Attack::Clone(void * pArg) {
	CMabubjin_Attack* pInstance = new CMabubjin_Attack(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CMabubjin_Attack : Clone");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMabubjin_Attack::Free() {
	__super::Free();
}