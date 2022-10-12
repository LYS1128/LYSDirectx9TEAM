#include "stdafx.h"
#include "..\Public\FireBall_Attack.h"

CFireBall_Attack::CFireBall_Attack(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CBoss_Skill(pGraphic_Device)
{
}

CFireBall_Attack::CFireBall_Attack(const CFireBall_Attack & rhs)
	:CBoss_Skill(rhs)
{
}

HRESULT CFireBall_Attack::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CFireBall_Attack : NativeConstruct_Prototype");
		return E_FAIL;
	}
	m_iDamagePercent = 3;
	return S_OK;
}

HRESULT CFireBall_Attack::NativeConstruct(void * pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CFireBall_Attack : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CFireBall_Attack : NativeConstruct");
		return E_FAIL;
	}
	m_eSkill = SKILL_FIREBALL;

	m_tBossSkillFrame.fFrame = 0.f;
	m_tBossSkillFrame.iSpriteEnd = 3;

	_float3 vPos = ((CBoss_Phase1::BOSSPATERN*)pArg)->vPosition;
	m_pTransform->Set_State(CTransform::STATE_POSITION, vPos);
	m_vLook = ((CBoss_Phase1::BOSSPATERN*)pArg)->vTargetLook;
	m_vLook.y -= 1.f;
	D3DXVec3Normalize(&m_vLook, &m_vLook);

	m_pTransform->Scaled(_float3(2.f, 2.f, 2.f));

	return S_OK;
}

void CFireBall_Attack::Tick(_float fTimeDelta) {
	BillBoard(m_pTransform);

	for (_uint i = 0; i <3; ++i)
	{
		_float3 Pos = m_pTransform->Get_State(CTransform::STATE_POSITION);
		if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Hit_Effect", L"Prototype_GameObject_FireParticle", &Pos))) {
			MSG_BOX(L"Failed To CEarthQuake : NativeConstruct");
			return;
		}
	}

	_float3 vPos = m_pTransform->Get_State(CTransform::STATE_POSITION);
	vPos += m_vLook * m_pTransform->Get_TransDesc().fSpeedPerSec * fTimeDelta;
	m_pTransform->Set_State(CTransform::STATE_POSITION, vPos);
}

void CFireBall_Attack::LateTick(_float fTimeDelta) {
	m_tBossSkillFrame.fFrame += m_tBossSkillFrame.iSpriteEnd * fTimeDelta;
	if ((_uint)m_tBossSkillFrame.fFrame >= m_tBossSkillFrame.iSpriteEnd) {
		m_tBossSkillFrame.fFrame = 0.f;
		++m_iTick;
	}
	if (5 <= m_iTick) {
		m_eState = STATE_DEAD;
	}
	m_pRenderer->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
}

HRESULT CFireBall_Attack::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CFireBall_Attack : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CFireBall_Attack::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 1.5f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CFireBall_Attack : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Boss_FireBall_Attack"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CFireBall_Attack : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CFireBall_Attack : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CFireBall_Attack : SetUp_Components");
		return E_FAIL;
	}
	return S_OK;
}

CFireBall_Attack * CFireBall_Attack::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CFireBall_Attack* pInstance = new CFireBall_Attack(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CFireBall_Attack : Create");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CFireBall_Attack::Clone(void * pArg) {
	CFireBall_Attack* pInstance = new CFireBall_Attack(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CFireBall_Attack : Clone");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CFireBall_Attack::Free() {
	__super::Free();
}