#include "stdafx.h"
#include "..\Public\BossHit_Effect.h"

CBossHit_Effect::CBossHit_Effect(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CBoss_Skill(pGraphic_Device)
{
}

CBossHit_Effect::CBossHit_Effect(const CBossHit_Effect & rhs)
	:CBoss_Skill(rhs)
{
}

HRESULT CBossHit_Effect::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CBossHit_Effect : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CBossHit_Effect::NativeConstruct(void * pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CBossHit_Effect : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CBossHit_Effect : NativeConstruct");
		return E_FAIL;
	}
	switch (((BOSSHIT*)pArg)->eSkill) {
	case SKILL_CLAW: {
		if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Boss_Claw_Effect"), (CComponent**)&m_pTexture))) {
			MSG_BOX(L"Failed To CBossHit_Effect : SetUp_Components");
			return E_FAIL;
		}
		m_tBossSkillFrame.iSpriteEnd = 4;
		break;
	}
	case SKILL_FIREBALL: {
		if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Boss_FireBall_Effect"), (CComponent**)&m_pTexture))) {
			MSG_BOX(L"Failed To CBossHit_Effect : SetUp_Components");
			return E_FAIL;
		}
		m_tBossSkillFrame.iSpriteEnd = 4;
		break;
	}
	case SKILL_MABUBJIN: {
		if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Boss_Mabubjin_Effect"), (CComponent**)&m_pTexture))) {
			MSG_BOX(L"Failed To CBossHit_Effect : SetUp_Components");
			return E_FAIL;
		}
		m_tBossSkillFrame.iSpriteEnd = 4;
		break;
	}
	case SKILL_METEOR:
	case SKILL_BLAST: {
		if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Boss_Meteor_Effect"), (CComponent**)&m_pTexture))) {
			MSG_BOX(L"Failed To CBossHit_Effect : SetUp_Components");
			return E_FAIL;
		}
		m_tBossSkillFrame.iSpriteEnd = 2;
		break;
	}
	case SKILL_ELECTRIC: {
		if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Electric_Effect"), (CComponent**)&m_pTexture))) {
			MSG_BOX(L"Failed To CBossHit_Effect : SetUp_Components");
			return E_FAIL;
		}
		m_tBossSkillFrame.iSpriteEnd = 3;
		break;
	}
	case SKILL_POG: {
		if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_PurplePog_Effect"), (CComponent**)&m_pTexture))) {
			MSG_BOX(L"Failed To CBossHit_Effect : SetUp_Components");
			return E_FAIL;
		}
		m_tBossSkillFrame.iSpriteEnd = 5;
		break;
	}
	default: {
		if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Boss_Meteor_Effect"), (CComponent**)&m_pTexture))) {
			MSG_BOX(L"Failed To CBossHit_Effect : SetUp_Components");
			return E_FAIL;
		}
		m_tBossSkillFrame.iSpriteEnd = 2;
		break;
	}
	}
	m_tBossSkillFrame.fFrame = 0.f;

	m_pTransform->Set_State(CTransform::STATE_POSITION, ((BOSSHIT*)pArg)->vPos);
	m_pTransform->Scaled(_float3(3.5f, 3.5f, 1.f));

	return S_OK;
}

void CBossHit_Effect::Tick(_float fTimeDelta) {
	__super::Tick(fTimeDelta);
}

void CBossHit_Effect::LateTick(_float fTimeDelta) {
	__super::LateTick(fTimeDelta);
}

HRESULT CBossHit_Effect::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBossHit_Effect : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CBossHit_Effect::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 1.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CBossHit_Effect : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CBossHit_Effect : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CBossHit_Effect : SetUp_Components");
		return E_FAIL;
	}
	return S_OK;
}

CBossHit_Effect * CBossHit_Effect::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CBossHit_Effect* pInstance = new CBossHit_Effect(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CBossHit_Effect : Create");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CBossHit_Effect::Clone(void * pArg) {
	CBossHit_Effect* pInstance = new CBossHit_Effect(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CBossHit_Effect : Clone");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CBossHit_Effect::Free() {
	__super::Free();
}