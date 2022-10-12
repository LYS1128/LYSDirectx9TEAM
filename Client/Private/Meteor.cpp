#include "stdafx.h"
#include "..\Public\Meteor.h"

CMeteor::CMeteor(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CBoss_Skill(pGraphic_Device)
{
}

CMeteor::CMeteor(const CMeteor & rhs)
	:CBoss_Skill(rhs)
{
}

HRESULT CMeteor::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CMeteor : NativeConstruct_Prototype");
		return E_FAIL;
	}
	m_iDamagePercent = 5;
	return S_OK;
}

HRESULT CMeteor::NativeConstruct(void * pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CMeteor : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CMeteor : NativeConstruct");
		return E_FAIL;
	}
	m_eSkill = SKILL_METEOR;

	m_tBossSkillFrame.fFrame = 0.f;
	m_tBossSkillFrame.iSpriteEnd = 8;

	m_pTransform->Set_State(CTransform::STATE_POSITION, _float3(_float(rand() % 16), 10.f, _float(rand() % 16)));
	
	m_pTransform->Scaled(_float3(3.f, 3.f, 1.f));

	return S_OK;
}

void CMeteor::Tick(_float fTimeDelta) {
	Compute_ZDis(m_pTransform);
	BillBoard(m_pTransform);

	_float3 vPos = m_pTransform->Get_State(CTransform::STATE_POSITION);

	if (vPos.y >= m_pTransform->Get_Scale().y * 0.5f) {
		vPos.y -= m_pTransform->Get_TransDesc().fSpeedPerSec * fTimeDelta;
		m_pTransform->Set_State(CTransform::STATE_POSITION, vPos);
		m_tBossSkillFrame.fFrame += m_tBossSkillFrame.iSpriteEnd * fTimeDelta;
		if ((_uint)m_tBossSkillFrame.fFrame >= 2) {
			m_tBossSkillFrame.fFrame = 0.f;
		}
	}
	else {
		for (_uint i = 0; i <3; ++i)
		{
			_float3 Pos = m_pTransform->Get_State(CTransform::STATE_POSITION);
			if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Hit_Effect", L"Prototype_GameObject_BossMeteor", &Pos))) {
				MSG_BOX(L"Failed To CEarthQuake : NativeConstruct");
				return;
			}
		}
		m_tBossSkillFrame.fFrame +=  m_tBossSkillFrame.iSpriteEnd * fTimeDelta;
		if ((_uint)m_tBossSkillFrame.fFrame >= m_tBossSkillFrame.iSpriteEnd) {
			m_tBossSkillFrame.fFrame = 0.f;
			m_eState = STATE_DEAD;
		}
	}
}

void CMeteor::LateTick(_float fTimeDelta) {
	m_pRenderer->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
}

HRESULT CMeteor::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CMeteor : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CMeteor::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = _float(rand() % 3 + 1);
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CBoss_Phase1 : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Boss_Meteor"), (CComponent**)&m_pTexture))) {
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

CMeteor * CMeteor::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CMeteor* pInstance = new CMeteor(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CMeteor : Create");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CMeteor::Clone(void * pArg) {
	CMeteor* pInstance = new CMeteor(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CMeteor : Clone");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMeteor::Free() {
	__super::Free();
}
