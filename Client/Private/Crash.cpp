#include "stdafx.h"
#include "..\Public\Crash.h"

CCrash::CCrash(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CBoss_Skill(pGraphic_Device)
{
}

CCrash::CCrash(const CCrash & rhs)
	:CBoss_Skill(rhs)
{
}

HRESULT CCrash::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CMabubjin_Attack : NativeConstruct_Prototype");
		return E_FAIL;
	}

	m_iDamagePercent = 2;
	return S_OK;
}

HRESULT CCrash::NativeConstruct(void * pArg) {
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
	m_tBossSkillFrame.iSpriteEnd = 4;

	_float3 vPos = *((_float3*)pArg);
	m_pTransform->Set_State(CTransform::STATE_POSITION, _float3(vPos.x,vPos.y-0.5f,vPos.z));

	m_pTransform->Set_State(CTransform::STATE_RIGHT, _float3(1.f, 0.f, 0.f));
	m_pTransform->Set_State(CTransform::STATE_UP, _float3(0.f, 0.f, -1.f));
	m_pTransform->Set_State(CTransform::STATE_LOOK, _float3(0.f, 1.f, 0.f));

	m_pTransform->Scaled(_float3(3.f,3.f, 3.f));
	return S_OK;
}

void CCrash::Tick(_float fTimeDelta) {
	MoveFrame(fTimeDelta);
}

void CCrash::LateTick(_float fTimeDelta) {
	__super::LateTick(fTimeDelta);
}

HRESULT CCrash::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CMabubjin_Attack : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CCrash::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 1.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(10.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CMabubjin_Attack : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Crash"), (CComponent**)&m_pTexture))) {
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

CCrash * CCrash::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CCrash* pInstance = new CCrash(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CMabubjin_Attack : Create");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CCrash::Clone(void * pArg) {
	CCrash* pInstance = new CCrash(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CMabubjin_Attack : Clone");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CCrash::Free() {
	__super::Free();
}