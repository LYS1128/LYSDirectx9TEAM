#include "stdafx.h"
#include "..\Public\PurplePog.h"

CPurplePog::CPurplePog(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CBoss_Skill(pGraphic_Device)
{
}

CPurplePog::CPurplePog(const CPurplePog & rhs)
	: CBoss_Skill(rhs)
{
}

HRESULT CPurplePog::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CPurplePog : NativeConstruct_Prototype");
		return E_FAIL;
	}
	
	m_iDamagePercent = 1;
	m_iDamage = 1;
	return S_OK;
}

HRESULT CPurplePog::NativeConstruct(void* pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CPurplePog : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CPurplePog : NativeConstruct");
		return E_FAIL;
	}

	m_eSkill = SKILL_POG;

	m_tBossSkillFrame.fFrame = 0.f;
	m_tBossSkillFrame.iSpriteEnd = 6;

	_float3 PlayerPos = dynamic_cast<CTransform*>(m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform"))->Get_State(CTransform::STATE_POSITION);
	m_pTransform->Set_State(CTransform::STATE_POSITION, PlayerPos);

	m_pTransform->Scaled(_float3(2.01f, 2.01f, 2.01f));

	_float3 Pos = m_pTransform->Get_State(CTransform::STATE_POSITION);

		for (_uint i = 0; i < 100; ++i)
			m_pGameInstance->Add_GameObjectToLayer(g_iLevel, L"Layer_Hit_Effect", L"Prototype_GameObject_Particle", &Pos);
	return S_OK;
}

void CPurplePog::Tick(_float fTimeDelta) {
	BillBoard(m_pTransform);
	m_tBossSkillFrame.fFrame += m_tBossSkillFrame.iSpriteEnd * fTimeDelta;
	if ((_uint)m_tBossSkillFrame.fFrame >= m_tBossSkillFrame.iSpriteEnd) {
		m_tBossSkillFrame.fFrame = 0.f;
	}
}

void CPurplePog::LateTick(_float fTimeDelta) {
	m_tBossSkillFrame.fFrame += m_tBossSkillFrame.iSpriteEnd * fTimeDelta;
	if ((_uint)m_tBossSkillFrame.fFrame >= m_tBossSkillFrame.iSpriteEnd) {
		m_tBossSkillFrame.fFrame = 3.f;
		++m_iTick;
	}
	++m_TickCount;
	if (360 <= m_TickCount) {
		m_eState = STATE_DEAD;
	}
	m_pRenderer->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
}

HRESULT CPurplePog::Render() {
	if (FAILED(__super::Render())) {	
		MSG_BOX(L"Failed To CPurplePog : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CPurplePog::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 1.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CPurplePog : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_PurplePog"), LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_PurplePog"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CPurplePog : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CPurplePog : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CPurplePog : SetUp_Components");
		return E_FAIL;
	}
	return S_OK;
}

CPurplePog* CPurplePog::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CPurplePog*	pInstance = new CPurplePog(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CPurplePog : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CPurplePog::Clone(void* pArg) {
	CPurplePog*	pInstance = new CPurplePog(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CPurplePog : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CPurplePog::Free() {
	__super::Free();
}