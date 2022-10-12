#include "stdafx.h"
#include "..\Public\Blast.h"

CBlast::CBlast(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CBoss_Skill(pGraphic_Device)
{
}

CBlast::CBlast(const CBlast & rhs)
	: CBoss_Skill(rhs)
{
}

HRESULT CBlast::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CBlast : NativeConstruct_Prototype");
		return E_FAIL;
	}
	m_iDamagePercent = 3;
	return S_OK;
}

HRESULT CBlast::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CBlast : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CBlast : NativeConstruct");
		return E_FAIL;
	}
	m_eSkill = SKILL_BLAST;

	m_tBossSkillFrame.fFrame = 0.f;
	m_tBossSkillFrame.iSpriteEnd = 6;

	CTransform* PlayerTrans = (CTransform*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform");
	_float3 PlayerPos = PlayerTrans->Get_State(CTransform::STATE_POSITION);
	m_pTransform->Set_State(CTransform::STATE_POSITION,PlayerPos + _float3(0.f,3.f,0.f));

	m_pTransform->Scaled(_float3(3.f, 3.f, 3.f));

	return S_OK;
}

void CBlast::Tick(_float fTimeDelta)
{
	BillBoard(m_pTransform);
	Compute_ZDis(m_pTransform);

	_float3 vPos = m_pTransform->Get_State(CTransform::STATE_POSITION);

	if (vPos.y >= m_pTransform->Get_Scale().y * 0.5f +8.f) {
		vPos.y -= m_pTransform->Get_TransDesc().fSpeedPerSec * fTimeDelta;
		m_pTransform->Set_State(CTransform::STATE_POSITION, vPos);
		m_tBossSkillFrame.fFrame += m_tBossSkillFrame.iSpriteEnd * fTimeDelta;
		if ((_uint)m_tBossSkillFrame.fFrame >=0) {
			m_tBossSkillFrame.fFrame = 0.f;
		}
	}
	else {
		if ((_uint)m_tBossSkillFrame.fFrame == 2 || (_uint)m_tBossSkillFrame.fFrame == 1)
		{
			for (int i = 0; i <5; ++i) {
				m_pGameInstance->Add_GameObjectToLayer(g_iLevel, L"Layer_Hit_Effect", L"Prototype_GameObject_BlastParticle", m_pTransform->Get_State(CTransform::STATE_POSITION));
			}
		}
		m_tBossSkillFrame.fFrame += m_tBossSkillFrame.iSpriteEnd * fTimeDelta;
		if ((_uint)m_tBossSkillFrame.fFrame >= m_tBossSkillFrame.iSpriteEnd) {
			m_tBossSkillFrame.fFrame = 0.f;
			if (m_pGameInstance->Find_Layer_List(LEVEL_STAGEBOSS, L"Layer_Boss")->size() != 0)
				m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEBOSS, L"Layer_BossSkill", L"Prototype_GameObject_Crash", &(m_pTransform->Get_State(CTransform::STATE_POSITION)));
			m_eState = STATE_DEAD;

			
		}
	}
}

void CBlast::LateTick(_float fTimeDelta)
{
	m_pRenderer->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
}

HRESULT CBlast::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBlast : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CBlast::SetUp_Components()
{
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 1.5f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CBlast : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Blast"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CBlast : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CBlast : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CBlast : SetUp_Components");
		return E_FAIL;
	}
	return S_OK;
}

CBlast * CBlast::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CBlast* pInstance = new CBlast(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CBlast : Create");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CBlast::Clone(void * pArg)
{
	CBlast* pInstance = new CBlast(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CBlast : Clone");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CBlast::Free()
{
	__super::Free();
}
